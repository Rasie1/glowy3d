#include "MainScene.h"
//#include "FileOperation.h"

//tasks list

//encapsulate movement into the ability
//start and end of level
//make ground a single sprite with smoothed texture
//separate decoration layer and make it hide when player is beneath them
//invisible walls should not be so invisible
//save objects to file, serialization
//memory leaks like 1mb per level load
//walls are placed wrong when the corridor is wider than room
//make hud
//popups
//write a new engine instead of cocos2d-x :D
//character sprite and animations
//think about character stats
//fix pathfinding issues
//make it handle bigger objects with radius
//AI: make them follow player
//update collision map often
//make texturegenerator work with full functionality
//make animations


Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//*
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	center = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	isMouseDown = false;

	auto closeItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	closeItem->setPosition(
		Vec2(
		origin.x + visibleSize.width
		- closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));;

	auto nextItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuNextCallback, this));
	nextItem->setPosition(
		Vec2(
		origin.x + visibleSize.width
		- closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height));

	auto menu = Menu::create(closeItem, nextItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 999);
	
	level = new WorldManager(this);
	level->init();
	delta = Vec2(0, 0);

	/* shader testing field
	auto spr = Sprite::create("HelloWorld.png");
		std::string vertexShader = ccPositionTextureColor_noMVP_vert;
	std::string fragmentShader = FileUtils::getInstance()->getStringFromFile(
		FileUtils::getInstance()->fullPathForFilename("Shaders/colorize_saturation.fsh"));

	spr->setGLProgram(GLProgram::createWithByteArrays(vertexShader.c_str(), fragmentShader.c_str()));
	spr->getGLProgramState()->setUniformVec4("u_rgbs", Vec4(1, 0, 1, 12.0));

	addChild(spr, 99999);
	//*/

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::keyboardPressCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	auto touchListener = EventListenerTouchOneByOne::create();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::touchBeganCallback, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::touchMovedCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::mouseMoveCallback, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MainScene::mouseUpCallback, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mouseDownCallback, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(MainScene::mouseScrollCallback, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	healthLabel = Label::create(std::to_string(level->getWorld()->player->getHealth()), "Arial", 12);
	healthLabel->setPosition(center / 5);
	addChild(healthLabel, 99999);
	this->schedule(schedule_selector(MainScene::updateFrame), 0.0166666666666f);
	this->schedule(schedule_selector(MainScene::updateSecond), 1.0f);
	this->schedule(schedule_selector(MainScene::updateTenth), 0.1f);

	level->getWorld()->map->saveToFile();
	//level->getWorld()->zoom(1.05f);
	return true;
}

void MainScene::updateFrame(float delayTime)
{
	level->getWorld()->updateFrame(delayTime / 0.0166666666666f);
}

void MainScene::updateSecond(float delayTime)
{
	level->getWorld()->updateSecond();
	TextureAssembler::getInstance()->clean();//overkill
}

void MainScene::updateTenth(float delayTime)
{
	level->getWorld()->updateTenth();
	if (isMouseDown)
		this->level->getWorld()->player->moveTo(level->getWorld()->convertToNodeSpace(cursorPos));
}

bool MainScene::touchBeganCallback(Touch * touch, Event * event)
{
	this->level->getWorld()->player->moveTo(level->getWorld()->convertToNodeSpace(touch->getLocation()));

	return true;
}

void MainScene::touchMovedCallback(Touch * touch, Event * event)
{
	this->level->getWorld()->player->useAbility(ABILITY_MOVETO, level->getWorld()->convertToNodeSpace(touch->getLocation()));

}

void MainScene::touchEndedCallback(Touch * touch, Event * event)
{

}

void MainScene::moveSpriteAnimationDone(Sprite * moveSprite)
{
	moveSprite->setVisible(false);
}

void MainScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::menuNextCallback(Ref* pSender)
{
	level->finish();
}

void MainScene::keyboardPressCallback(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		delta += Vec2(0, -3);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		delta += Vec2(0, 3);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		delta += Vec2(-3, 0);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		delta += Vec2(3, 0);
		break;
	case EventKeyboard::KeyCode::KEY_1:
		delta = Vec2(0, 0);
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		this->menuCloseCallback(this);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		level->getWorld()->player->useAbility(ABILITY_ATTACK);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		level->getWorld()->map->collision->saveToFile();
		break;
	case EventKeyboard::KeyCode::KEY_9:
			level->getWorld()->zoomIn();
		break;
	case EventKeyboard::KeyCode::KEY_0:
		level->getWorld()->zoomOut();
		break;
	default:
		break;
	}
}

void MainScene::mouseDownCallback(Event *event)
{
	//str += tostr(e->getMouseButton());
	EventMouse * e = (EventMouse*)event;
	if (!level->getWorld()->overlay->tryTouching(level->getWorld()->convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()))))
		isMouseDown = true;

}

void MainScene::mouseUpCallback(Event *event)
{
	//str += tostr(e->getMouseButton());
	isMouseDown = false;
}

void MainScene::mouseMoveCallback(Event *event)
{
	EventMouse * e = (EventMouse*)event;
	cursorPos = Vec2(e->getCursorX(), e->getCursorY());
	level->getWorld()->overlay->hover(level->getWorld()->convertToNodeSpace(cursorPos));
}

void MainScene::mouseScrollCallback(Event *event)
{
	EventMouse * e = (EventMouse*)event;
	//str = str + tostr(e->getScrollX()) + " Y: " + tostr(e->getScrollY());
}