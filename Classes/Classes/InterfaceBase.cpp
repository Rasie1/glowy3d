#include "InterfaceBase.h"
#include <iostream>
#include "FileOperation.h"

//InterfacePart

InterfacePart * InterfacePart::create(MapInfo * map, Ability * action, Rect rect, Texture2D * texture, Vec2 textureOffset)
{
	InterfacePart * ret = new InterfacePart();

	if (ret && ret->init(map, action, rect, texture, textureOffset))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool InterfacePart::init(MapInfo * map, Ability * action, Rect rect, Texture2D * texture, Vec2 textureOffset)
{
	textured = false;
	if (texture != nullptr)
	{
		sprite = Sprite::createWithTexture(texture);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(rect.origin + textureOffset);
		textured = true;
	}
	this->map = map;
	this->action = action;
	this->textureDefault = texture;
	this->textureHover = texture;
	this->texturePressed = texture;
	this->rect = rect;
	this->hovering = false;
	return true;
}

void InterfacePart::activate()
{
	action->apply();
}

bool InterfacePart::tryTouching(Vec2 position)
{
	if (isInside(position))
	{
		activate();
		return 1;
	}
	return 0;
}

bool InterfacePart::hover(Vec2 position)
{
	if (hovering)
		return 1;
	if (isInside(position))
	{
		onHover();
		return 1;
	}
	return 0;
}

Sprite * InterfacePart::getSprite()
{
	return sprite;
}

bool InterfacePart::isTextured()
{
	return textured;
}

void InterfacePart::onHover()
{
	hovering = true;
}

void InterfacePart::onHoverEnd()
{
	hovering = false;
}

bool InterfacePart::isHovering()
{
	return hovering;
}

bool InterfacePart::isInside(Vec2 point)
{
	return rect.containsPoint(point);
}

//InterfacePartActor

InterfacePartActor * InterfacePartActor::create(Actor * actor)
{
	InterfacePartActor * ret = new InterfacePartActor();

	if (ret && ret->init(actor))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool InterfacePartActor::init(Actor * actor)
{
	InterfacePart::init(actor->map, actor->map->player->getAbility(ABILITY_ATTACK), Rect(actor->getPositionX() - actor->getRadius() / 2, actor->getPositionY() - actor->getRadius() / 2, actor->getRadius(), actor->getRadius()), nullptr, Vec2(0,0));
	this->actor = actor;
	return true;
}

void InterfacePartActor::activate()
{
	if (map->player->getAttackRangeSq() < actor->getPosition().getDistanceSq(map->player->getPosition()))
		map->player->moveTo(actor->getPosition());
	else
		action->apply();
}

void InterfacePartActor::onHover()
{
	InterfacePart::onHover();
	actor->setColor(Color3B(55, 255, 55));
}

void InterfacePartActor::onHoverEnd()
{
	InterfacePart::onHoverEnd();
	actor->setColor(Color3B(255, 255, 255));
}

//InterfaceBase

bool InterfaceBase::tryTouching(Vec2 position)
{
	int n = parts.size();
	bool wasTouched = 0;
	for (int i = 0; i < n; ++i)
		wasTouched += parts[i]->tryTouching(position); //incrementing bool
	return wasTouched;
}

InterfaceBase * InterfaceBase::create(MapInfo * map)
{
	InterfaceBase *ret = new InterfaceBase();
	
	if (ret && ret->init(map))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool InterfaceBase::init(MapInfo * map)
{
	this->map = map;
	hovered = nullptr;
	return true;
}

void InterfaceBase::add(InterfacePart * part)
{
	parts.push_back(part);
	part->retain();
	if (part->isTextured())
		this->addChild(part->getSprite(), 1000 + parts.size()); 
}

void InterfaceBase::remove(InterfacePart * part)
{
	for (int i = parts.size() - 1; i >= 0; --i)
	if (parts[i] == part)
	{
		if (hovered == part)
		{
			part->onHoverEnd();
			hovered = nullptr;
		}
		if (part->isTextured())
			this->removeChild(part->getSprite());
		parts.erase(parts.begin() + i);
		part->release();
		break;
	}
}

InterfaceBase::~InterfaceBase()
{
	int n = parts.size();
	for (int i = 0; i < n; ++i)
	{
		parts.back()->release();
		parts.pop_back();
	}
}

bool InterfaceBase::hover(Vec2 position)
{
	if (hovered != nullptr)
	{
		if (!hovered->isInside(position))
		{
			hovered->onHoverEnd();
			hovered = nullptr;
		}
	}
	for (int i = parts.size() - 1; i >= 0; --i)
	{
		if (parts[i]->hover(position))
		{
			hovered = parts[i];
			return 1;
		}
	}
	return 0;
}
/*
//WeatherEffects

void WeatherEffects::setMoveVector(Vec2 delta)
{
	state->setUniformVec2("u_movement", delta);
}

WeatherEffects::WeatherEffects(World * level)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto center = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	this->level = level;
	Texture2D::TexParams p;
	p.minFilter = GL_LINEAR;
	p.magFilter = GL_LINEAR;
	p.wrapS = GL_REPEAT;
	p.wrapT = GL_REPEAT;

	auto cloudsSprite = Sprite::create("noise_1024.png");
	cloudsSprite->getTexture()->setTexParameters(p);
	cloudsSprite->setPosition(center);
	cloudsSprite->setTag(10);
	float cloudsScaleX = visibleSize.width / cloudsSprite->getContentSize().width;
	float cloudsScaleY = visibleSize.height / cloudsSprite->getContentSize().height;
	cloudsSprite->setScaleX(cloudsScaleX);
	cloudsSprite->setScaleY(cloudsScaleY);
	level->addChild(cloudsSprite, 10);

	auto textureCache = Director::getInstance()->getTextureCache();
	auto tex1 = textureCache->addImage("noise_512.png");
	tex1->setTexParameters(p);

	auto tex2 = textureCache->addImage("noise_256.png");
	tex2->setTexParameters(p);

	// Create the clouds shader
	GLProgram* prog = new GLProgram();
	prog->initWithFilenames("clouds.vs", "clouds.fs");

	prog->link();
	prog->use();
	prog->updateUniforms();

	glActiveTexture(GL_TEXTURE1);
	CHECK_GL_ERROR_DEBUG();
	glBindTexture(GL_TEXTURE_2D, tex1->getName());
	CHECK_GL_ERROR_DEBUG();

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex2->getName());
	CHECK_GL_ERROR_DEBUG();

	glActiveTexture(GL_TEXTURE0);
	CHECK_GL_ERROR_DEBUG();

	ShaderCache::getInstance()->addGLProgram(prog, "clouds");

	cloudsSprite->setGLProgram(prog);
	state = GLProgramState::getOrCreateWithGLProgram(prog);
	//state->setUniformFloat("u_cloudSpeed", 0.7);
	state->setUniformVec2("u_movement", Vec2(0, 0));
	state->setUniformFloat("u_amount", 1);

	prog->release();
}*/