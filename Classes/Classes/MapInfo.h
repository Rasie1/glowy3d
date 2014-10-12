#ifndef __MAP_INFO_H__
#define __MAP_INFO_H__

#include "cocos2d.h"
#include "MapGenerator.h"
#include "World.h"
#include "TileInfo.h"
#include "Tileset.h"
#include "Libs.h"
#include "Actor.h"
#include "Creature.h"
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
class CollisionMap;
struct Vec2i;
struct Recti;


class MapInfo : public Ref
{
public:
	virtual bool init(int type, Size size);
	static MapInfo * create(int type, Size size);

	Size mapSize;
	int tileSize;
	int mapType;
	Vec2 playerStart;

	MapGenerator * generator;
	Tileset * tileset;

	TileInfo *** tiles;
	CollisionMap * collision;
	Vector<Actor*> actors;
	Player * player;
	World * world;

	void update();

	void saveToFile(std::string fileName = "map.txt");

	void addActor(Actor * actor);

	void setPlaying(bool isPlaying);
private:
	bool isPlaying;

	MapInfo() {}
	~MapInfo();
};


class CollisionMap : public Ref
{
public:
	static CollisionMap * create(MapInfo * info);
	bool init(MapInfo * info);

	bool isWalkable(Vec2i point);
	bool isWalkable(Vec2i point, int radius);
	bool isWalkable(Vec2 point);
	bool isWalkable(Vec2 point, int radius);
	void setCollision(Vec2i point, bool isWalkable);
	void setCollision(Vec2 point, bool isWalkable);
	void setCollision(Vec2 point, int radius, bool isWalkable);
	bool ** map;

	void update();
	void saveToFile(std::string fileName = "mapc.txt");
private:
	CollisionMap() {}
	~CollisionMap();

	inline void CollisionMap::fillTiles(int x, int y, int x1, int y1, bool val);

	MapInfo * level;
};

#endif
