#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Actor.h"
USING_NS_CC;

class MapInfo;

/*
class xMapNode
{
public:
	xMapNode(const Vec2& position) : m_pos(position) {}
	Vec2 m_pos;
};

class xMapNodeRoom : public xMapNode
{
public:
	xMapNodeRoom(const Vec2& position, const Vec2& size) : m_pos(position), m_size(size) {}

	Vec2 m_size;
protected:
};*/






class MapNode : public Ref
{
public:

	std::vector<MapNode*> links;
	static MapNode * create(const Vec2& pos);
	virtual bool init(const Vec2& pos);
	virtual bool apply(MapInfo * map);

	int getImportance();
	void setImportance(int amount);

protected:
	Vec2 pos;
	Size size;
	int importance;
	MapNode() {}
};


//Regular-sized square room
class RoomMapNode : public MapNode
{
public:
	static RoomMapNode * create(const Vec2& cornerLeft, const Vec2& cornerRight);
	//Creates with entrance in wall
	static RoomMapNode * create(const Vec2& cornerLeft, const Vec2& cornerRight, int direction, int gapStart, int gapEnd);
	virtual bool init(const Vec2& cornerLeft, const Vec2& cornerRight);
	//Inits with entrance in wall
	virtual bool init(const Vec2& cornerLeft, const Vec2& cornerRight, int direction, int gapStart, int gapEnd);
	virtual bool apply(MapInfo * map);

protected:
	RoomMapNode() {}

	Vec2 pos2;
	int direction, gapStart, gapEnd;
};

//A room without two walls, depending on direction
class CorridorMapNode : public RoomMapNode
{
public:
	static CorridorMapNode * create(const Vec2& cornerLeft, const Vec2& cornerRight, int direction);
	virtual bool init(const Vec2& cornerLeft, const Vec2& cornerRight, int direction);

	virtual bool apply(MapInfo * map);

protected:
	CorridorMapNode() {}
	int direction;
};

class WallMapNode : public MapNode
{
public:
	static WallMapNode * create(const Vec2& corner1, const Vec2& corner2, int direction);
	virtual bool init(const Vec2& corner1, const Vec2& corner2, int direction);
	virtual bool apply(MapInfo * map);

	void use();
	void addEntrance(int entranceStart = 0, int entranceEnd = 0);

	bool isUsed();
	int getDirection();
	Vec2 getWallStart();
	Vec2 getWallEnd();

protected:
	WallMapNode() {}
	bool used;
	Vec2 wallStart, wallEnd;
	int gapStart, gapEnd, direction;
};
/*
class WallEntranceMapNode : public WallMapNode
{
public:
	static WallMapNode * create(const Vec2& corner1, const Vec2& corner2, int direction);
	virtual bool init(const Vec2& corner1, const Vec2& corner2, int direction);
	virtual bool apply(MapInfo * map);

	void use();
	void addEntrance(int entranceStart = 0, int entranceEnd = 0);

	bool isUsed();
	int getDirection();
	Vec2 getWallStart();
	Vec2 getWallEnd();

protected:
	WallEntranceMapNode() {}
	bool used;
	Vec2 wallStart, wallEnd;
	int gapStart, gapEnd, direction;
};*/

class WallCornerMapNode : public MapNode
{
public:

protected:
	WallCornerMapNode() {}
};

#endif