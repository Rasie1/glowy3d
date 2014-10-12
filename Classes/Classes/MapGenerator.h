#ifndef __MAP_GENERATOR_H__
#define __MAP_GENERATOR_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Actor.h"
#include "MapNode.h"
#include "Tileset.h"
#include "TilesetGenerator.h"
USING_NS_CC;

class MapInfo;
class MapNode;
class RoomMapNode;
class CorridorMapNode;
class Tileset;
class TilesetGenerator;


//Generates map. Call inside MapInfo
class MapGenerator : public Ref
{
public:
	virtual bool init(Size size, MapInfo * map);
	MapGenerator * create(Size size, MapInfo * sender);

	virtual void generate();

	MapNode * getRandomNode();
	void addOpenNode(MapNode * node);
protected:
	MapGenerator() {}

	MapNode * graph;

	Size mapSize;
	MapInfo * map;
private:
protected:
	Vector <MapNode*> openNodes;
};

class DungeonMapGenerator : public MapGenerator
{
public:
	virtual bool init(Size size, MapInfo * map);
	static DungeonMapGenerator * create(Size size, MapInfo * map);
	virtual void generate();
private:
	DungeonMapGenerator() {}
	//void generateRecursion(MapNode * node);
	int powerPoints;
};



#endif