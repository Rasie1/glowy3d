#include "MapNode.h"

//MapNode

MapNode * MapNode::create(const Vec2& pos)
{
	MapNode * ret = new MapNode();
	if (ret && ret->init(pos))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MapNode::init(const Vec2& pos)
{
	this->pos = pos;
	return 1;
}

bool MapNode::apply(MapInfo * map)
{
	return 1;
}

int MapNode::getImportance()
{
	return importance;
}

void MapNode::setImportance(int amount)
{
	importance = amount;
}

//RoomMapNode

RoomMapNode * RoomMapNode::create(const Vec2& cornerLeft, const Vec2& cornerRight)
{
	RoomMapNode * ret = new RoomMapNode();
	if (ret && ret->init(cornerLeft, cornerRight))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

RoomMapNode * RoomMapNode::create(const Vec2& cornerLeft, const Vec2& cornerRight, int direction, int gapStart, int gapEnd)
{
	RoomMapNode * ret = new RoomMapNode();
	if (ret && ret->init(cornerLeft, cornerRight, direction, gapStart, gapEnd))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool RoomMapNode::init(const Vec2& cornerLeft, const Vec2& cornerRight)
{
	MapNode::init(cornerLeft);
	this->pos2 = cornerRight;
	size = cornerRight - cornerLeft;
	return 1;
}
bool RoomMapNode::init(const Vec2& cornerLeft, const Vec2& cornerRight, int direction, int gapStart, int gapEnd)
{
	MapNode::init(cornerLeft);
	this->pos2 = cornerRight;
	size = cornerRight - cornerLeft;
	this->direction = direction;
	this->gapEnd = gapEnd;
	this->gapStart = gapStart;
	return 1;
}

bool RoomMapNode::apply(MapInfo * map)
{
	int n = std::min(map->mapSize.width - 2, pos2.x);
	int m = std::min(map->mapSize.height - 2, pos2.y);
	int startx = std::max(1, (int)pos.x);
	int starty = std::max(1, (int)pos.y);
	for (int i = startx; i <= n; ++i)
	for (int j = starty; j <= m; ++j)
	{
		//map->tiles[j][i]->release();
		map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
		//map->actors[j][i] = (rand() % 30) ? 0 : 1 + rand() % 2;
	}
	auto north = WallMapNode::create(Vec2(startx + 1, starty), Vec2(n - 1, starty), DIRECTION_N);
	if (direction == DIRECTION_S)
		north->addEntrance(gapStart, gapEnd);
	north->apply(map);
	auto east = WallMapNode::create(Vec2(n, starty + 1), Vec2(n, m - 1), DIRECTION_E);
	if (direction == DIRECTION_W)
		east->addEntrance(gapStart, gapEnd);
	east->apply(map);
	auto south = WallMapNode::create(Vec2(startx + 1, m), Vec2(n - 1, m), DIRECTION_S);
	if (direction == DIRECTION_N)
		south->addEntrance(gapStart, gapEnd);
	south->apply(map);
	auto west = WallMapNode::create(Vec2(startx, starty + 1), Vec2(startx, m - 1), DIRECTION_W);
	if (direction == DIRECTION_E)
		west->addEntrance(gapStart, gapEnd);
	west->apply(map);
	map->generator->addOpenNode(north);
	map->generator->addOpenNode(east);
	map->generator->addOpenNode(south);
	map->generator->addOpenNode(west);

	map->tiles[starty][startx] = TileInfo::create(map->tileset->getByType(TILE_WALL_CORNER_LEFT), TILE_WALL_CORNER_LEFT);
	map->tiles[starty][n] = TileInfo::create(map->tileset->getByType(TILE_WALL_CORNER_UP), TILE_WALL_CORNER_UP);
	map->tiles[m][startx] = TileInfo::create(map->tileset->getByType(TILE_WALL_CORNER_DOWN), TILE_WALL_CORNER_DOWN);
	map->tiles[m][n] = TileInfo::create(map->tileset->getByType(TILE_WALL_CORNER_RIGHT), TILE_WALL_CORNER_RIGHT);
	return 1;
}

//CorridorMapNode

CorridorMapNode * CorridorMapNode::create(const Vec2& cornerLeft, const Vec2& cornerRight, int direction)
{
	CorridorMapNode * ret = new CorridorMapNode();
	if (ret && ret->init(cornerLeft, cornerRight, direction))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool CorridorMapNode::init(const Vec2& cornerLeft, const Vec2& cornerRight, int direction)
{
	RoomMapNode::init(cornerLeft, cornerRight);
	this->direction = direction;
	return 1;
}

bool CorridorMapNode::apply(MapInfo * map)
{
	int n = std::min(map->mapSize.width - 2, pos2.x);
	int m = std::min(map->mapSize.height - 2, pos2.y);
	int startx = std::max(1, (int)pos.x);
	int starty = std::max(1, (int)pos.y);
	for (int i = startx; i <= n; ++i)
	for (int j = starty; j <= m; ++j)
	{
		//map->tiles[j][i]->release(); leak?
		map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
		//map->actors[j][i] = (rand() % 30) ? 0 : 1 + rand() % 2;
	}
	if (direction == DIRECTION_N || direction == DIRECTION_S)
	{
		auto west = WallMapNode::create(Vec2(startx, starty), Vec2(startx, m), DIRECTION_W);
		west->apply(map);
		auto east = WallMapNode::create(Vec2(n, starty), Vec2(n, m), DIRECTION_E);
		east->apply(map);
		map->generator->addOpenNode(west);
		map->generator->addOpenNode(east);
	}
	else
	{
		auto north = WallMapNode::create(Vec2(startx, starty), Vec2(n, starty), DIRECTION_N);
		north->apply(map);
		auto south = WallMapNode::create(Vec2(startx, m), Vec2(n, m), DIRECTION_S);
		south->apply(map);
		map->generator->addOpenNode(north);
		map->generator->addOpenNode(south);
	}
	return 1;
}

//WallMapNode

WallMapNode * WallMapNode::create(const Vec2& corner1, const Vec2& corner2, int direction)
{
	WallMapNode * ret = new WallMapNode();
	if (ret && ret->init(corner1, corner2, direction))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool WallMapNode::init(const Vec2& corner1, const Vec2& corner2, int direction)
{
	MapNode::init(corner1.getMidpoint(corner2));
	this->direction = direction;
	used = false;
	if (direction == DIRECTION_N || direction == DIRECTION_S)
	{
		if (corner1.x > corner2.x)
		{
			wallStart = corner2;
			wallEnd = corner1;
		}
		else
		{
			wallStart = corner1;
			wallEnd = corner2;
		}
	}
	else
	{
		if (corner1.y > corner2.y)
		{
			wallStart = corner2;
			wallEnd = corner1;
		}
		else
		{
			wallStart = corner1;
			wallEnd = corner2;
		}
	}
	size = Size(rand() % 6 + 4, rand() % 6 + 4);
	return 1;
}

bool WallMapNode::apply(MapInfo * map)
{
	int j = std::max((int)wallStart.y, 1);
	int i = std::max((int)wallStart.x, 1);
	int n = std::min(wallEnd.x, map->mapSize.width - 1);
	int m = std::min(wallEnd.y, map->mapSize.height - 1);

	if (direction == DIRECTION_N)
	{
		for (; i <= n; ++i)
		{
			//map->tiles[j][i]->release();
			if (i < gapStart || i > gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_WALL_NORTH), TILE_WALL_NORTH);
			else if (i == gapStart)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else if (i == gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
		}
	}
	else if (direction == DIRECTION_E)
	{
		for (; j <= m; ++j)
		{
			//map->tiles[j][i]->release();
			if (j < gapStart || j > gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_WALL_EAST), TILE_WALL_EAST);
			else if (j == gapStart)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else if (j == gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
		}
	}
	else if (direction == DIRECTION_S)
	{
		for (; i <= n; ++i)
		{
			//map->tiles[j][i]->release();
			if (i < gapStart || i > gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_WALL_SOUTH), TILE_WALL_SOUTH);
			else if (i == gapStart)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else if (i == gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
		}
	}
	else if (direction == DIRECTION_W)
	{
		for (; j <= m; ++j)
		{
			//map->tiles[j][i]->release();
			if (j < gapStart || j > gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_WALL_WEST), TILE_WALL_WEST);
			else if (j == gapStart)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else if (j == gapEnd)
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
			else
				map->tiles[j][i] = TileInfo::create(map->tileset->getByType(TILE_GROUND), TILE_GROUND);
		}
	}
	return 1;
}

bool WallMapNode::isUsed()
{
	return used;
}

void WallMapNode::use()
{
	used = true;
}

void WallMapNode::addEntrance(int entranceStart, int entranceEnd)
{
	use();
	gapStart = entranceStart;
	gapEnd = entranceEnd;
}

int WallMapNode::getDirection()
{
	return direction;
}

Vec2 WallMapNode::getWallStart()
{
	return wallStart;
}

Vec2 WallMapNode::getWallEnd()
{
	return wallEnd;
}