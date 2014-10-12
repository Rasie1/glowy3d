#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Actor.h"
#include "MapInfo.h"
#include "World.h"
#include "InterfaceBase.h"
#include "Creature.h"
#include "Player.h" 

USING_NS_CC;

class Ability;
class Actor;
class Creature;
class Player;
class Effect;
class World;
class TextureAssembler;
class MapInfo;
class WorldManager;
class InterfaceBase;
/*

class WorldInfo
{
public:

private:
}*/


class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	WorldManager * level;

	//called each frame
	void updateFrame(float delayTime);
	//called each second
	void updateSecond(float delayTime);
	//called ten times per second
	void updateTenth(float delayTime);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuNextCallback(cocos2d::Ref* pSender);
	void keyboardPressCallback(EventKeyboard::KeyCode keyCode, Event * event);
	bool touchBeganCallback(Touch * touch, Event * event);
	void touchMovedCallback(Touch * touch, Event * event);//не оптимальна
	void touchEndedCallback(Touch * touch, Event * event); 
	void mouseDownCallback(Event * event);
	void mouseUpCallback(Event * event);
	void mouseMoveCallback(Event * event);
	void mouseScrollCallback(Event * event);
	CREATE_FUNC(MainScene);

	Label * healthLabel;

	MainScene() {}

	Vec2 delta;
	Size visibleSize;
	Vec2 origin, center;
private:
	Vec2 cursorPos;
	bool isMouseDown;
	Sprite * moveSprite;
	void moveSpriteAnimationDone(Sprite * moveSprite);
};

#endif
