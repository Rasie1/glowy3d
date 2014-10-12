#ifndef __WORLD_H__
#define __WORLD_H__

#include "cocos2d.h"
#include "Actor.h"
#include "Creature.h"
#include "Player.h"
#include "MapGenerator.h"
#include "Libs.h"
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
class MapInfo;
class TileInfo;
class InterfaceBase;

class TileSprite : public Sprite
{
public:
	static TileSprite * create(Texture2D * tex, const Vec2& pos);
	static TileSprite * create(TileInfo * tile, const Vec2& pos);
	bool init(Texture2D * tex, const Vec2& globalPos);
private:
	TileSprite() {}
};

//Physical World representing rendering. See MapInfo for logical part
class World : public Layer
{
public:
	static World * create(MapInfo * currentMap);
	bool init(MapInfo * currentMap);
	static World & instance; //remove

	MapInfo * map;
	InterfaceBase * overlay;

	Creature * cr;

	WeatherEffects * weather;
	Player * player;
	TileSprite *** tiles;

	void updateFrame(float timeCoefficient);
	void updateTenth();
	void updateSecond();
	Vec2 findCollision(Vec2 from, const Vec2& to, const Vec2& step);
	Vec2 cutIfCollided(const Vec2& from, const Vec2& delta);

	void zoom(float k);
	void zoomIn();
	void zoomOut();
	void scroll();
	Vector<Actor*> localActors;

	void addActor(Actor * actor);
private:
	World() {}

	void updateSpritesVisibility();
	void updateLocalActorsVector();

	Vec2 _renderingCenterPosition, _cameraCenterPosition;
	int _spritesVisibleRadiusSquared;
	int _spritesInvisibleRadius;

	float zoomFactor = 1.00f;
};


class WorldManager
{
public:
	World * getWorld();

	bool init();

	//Call when end is reached
	void finish();
	//Creates new world. Draws automatically
	WorldManager(Node * parentForDrawing) : parent(parentForDrawing) {}
private:
	Node * parent;
	MapInfo * map;
	World * world;
	Player * player;
	InterfaceBase * overlay;

	void nextWorld();
	void initInterface();
};

#endif
