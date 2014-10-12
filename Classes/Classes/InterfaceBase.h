#ifndef __INTERFACE_BASE_H__
#define __INTERFACE_BASE_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Actor.h"
#include "Creature.h"
#include "MapGenerator.h"
#include "World.h"
#include "TileInfo.h"
#include "Player.h"
USING_NS_CC;

class Actor;
class Creature;
class Player;
class Tileset;
class MapGenerator;
class DungeonMapGenerator;
class WeatherEffects;
class InterfaceBase;
class Ability;
class Effect;
class World;
class TileInfo;
class MapInfo;

class InterfacePart : public Ref
{
public:
	static InterfacePart * create(MapInfo * map, Ability * action, Rect rect, Texture2D * texture = nullptr, Vec2 textureOffset = Vec2(0, 0));
	virtual bool init(MapInfo * map, Ability * action, Rect rect, Texture2D * texture, Vec2 textureOffset);

	virtual void activate();
	virtual void onHover();
	virtual void onHoverEnd();

	bool tryTouching(Vec2 position);
	bool hover(Vec2 position);

	void setHoverTexture(Texture2D * texture);
	void setPressedTexture(Texture2D * texture);
	//void setHoverTexture(Texture2D * texture);

	Sprite * getSprite();
	bool isTextured();
	bool isHovering();
	bool isInside(Vec2 point);
protected:
	InterfacePart() {}
	MapInfo * map;
	Ability * action;
	Texture2D * textureDefault;
	Texture2D * textureHover;
	Texture2D * texturePressed;

	Rect rect;
	Sprite * sprite;
	bool textured, hovering;
};

class InterfacePartActor : public InterfacePart
{
public:
	static InterfacePartActor * create(Actor * actor);
	virtual bool init(Actor * actor);

	virtual void activate();
	virtual void onHover();
	virtual void onHoverEnd();
private:
	Actor * actor;
	InterfacePartActor() {}
};

//class OverlayInfo : Sprite()

//a class for interface and objects that depend from player position
class InterfaceBase : public Layer
{
public:
	static InterfaceBase * create(MapInfo * map);
	virtual bool init(MapInfo * map);

	bool touchBeganCallback(Touch * touch, Event * event);
	//returns true if touch is grabbed
	bool tryTouching(Vec2 position);
	bool hover(Vec2 position);

	void add(InterfacePart * part);
	void remove(InterfacePart * part);
private:
	std::vector<InterfacePart*> parts;
	InterfacePart * hovered;
	MapInfo * map;
	InterfaceBase() {}
	~InterfaceBase();
};

/*
class WeatherEffects
{
public:
	WeatherEffects(MapInfo * map);
	void setMoveVector(Vec2 delta);
private:
	MapInfo * map;
	GLProgramState * state;
};*/


#endif
