#ifndef __MAP_PATH_H__
#define __MAP_PATH_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Actor.h"
#include "MapNode.h"
#include "TileInfo.h"
#include "Libs.h"

class MapInfo;
struct Vec2i;
struct Vec2iv;

USING_NS_CC;

//Path represented by points
class MapPath : public Ref
{
public:
	static MapPath * create(Creature * creature);
	bool init(Creature * creature);

	Vec2 back();
	void next();
	void setDestination(const Vec2& to);
	void findPath();
	bool isEmpty();

	bool isGettingToThePoint;

	std::list<Vec2> path;
private:
	std::list<Vec2>::iterator currentMovementTarget;

	//Primary pathfinding
	std::map<Vec2i, bool> inOpen;
	std::set<Vec2i> closed;
	std::map<Vec2i, Vec2i> parents;
	std::map<Vec2i, int> lengths;
	std::vector<Vec2iv> open;

	//For fixing unwalkable pathes
	std::vector<Vec2iv> open2;
	std::map<Vec2i, bool> inOpen2;
	std::set<Vec2i> closed2;
	std::map<Vec2i, Vec2i> parents2;
	std::map<Vec2i, int> lengths2;

	MapInfo * map;
	Creature * creature;
	bool ** walk;
	Vec2 from;
	Vec2 target;
	Vec2 to;
	Vec2 oldTo;
	//Vec2i fr;
	//Vec2i to;
	int maxOperations, tileSize4, newLength, n;
	MapPath() {}

	void processPoint(const Vec2i& point, const Vec2i& parent);
	void processPointInTargetFixing(const Vec2i& point, const Vec2i& parent);
	int cost(const Vec2i& point);
	void checkAndFixTarget();

	void updateOpenHeap(int i, int value);
	bool isDone;
};


//Path represented by points : new ver
class Pathfinder : public Ref
{
public:
	static Pathfinder * create(Creature * creature);
	bool init(Creature * creature);

	void setDestination(const Vec2& to);

	Vec2 getNextPoint();
	bool isMoving();

private:
	bool  m_isMoving;
	Creature * creature;
	Vec2 m_target;
	Vec2i * m_to;

	bool ** walk;

	std::list<Vec2> finalPath;

	//<A-Star parts>
	std::map<Vec2i, bool> inOpen;
	std::set<Vec2i> closed;
	std::map<Vec2i, Vec2i> parents;
	std::map<Vec2i, int> lengths;
	std::vector<Vec2iv> open;

	int cost(const Vec2i& point);
	void processPoint(const Vec2i& point, const Vec2i& parent);

	int n, newLength;
	//</A-Star parts>

	void findPath();

	Pathfinder() {}
	~Pathfinder();
};

#endif