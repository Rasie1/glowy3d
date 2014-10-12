#include "MapInfo.h"
#include <iostream>
#include "FileOperation.h"

MapInfo * MapInfo::create(int type, Size size)
{
	MapInfo *ret = new MapInfo();
	if (ret && ret->init(type, size))
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

bool MapInfo::init(int type, Size size)
{
	this->mapSize = size;
	this->mapType = type;
	this->tileSize = 256;
	this->tileset = (TilesetGenerator::create())->getTileset();
	this->playerStart = Vec2((int)(size.width / 2), (int)(size.height / 2));
	tiles = new TileInfo**[(int)size.height];

	for (int i = 0; i < size.height; ++i)
	{
		tiles[i] = new TileInfo*[(int)size.width];
	}

	generator = DungeonMapGenerator::create(this->mapSize, this);
	generator->generate();

	collision = CollisionMap::create(this);
	collision->retain();

	int monstersAmount = 30;

	Vec2 actorPosition;
	while (--monstersAmount)
	{
		do
		{
			actorPosition = Vec2(rand() % int(mapSize.width * 4), rand() % int(mapSize.height * 4));
		} while (collision->isWalkable(actorPosition) == false);
		actors.pushBack(Creature::create(tileToCoord(actorPosition, tileSize / 4), this));
	}

	return 1;
}

void MapInfo::saveToFile(std::string fileName)
{
	std::string path = "map.txt";
	FILE *fp = fopen(path.c_str(), "w");

	if (!fp)
	{
		CCLOG("can not create file %s", path.c_str());
		return;
	}

	for (int i = 0; i < mapSize.height; ++i)
	{
		for (int j = 0; j < mapSize.width; ++j)
			std::fputc(48 + tiles[i][j]->getType(), fp);
		std::fputc('\n', fp);
	}
	fclose(fp);
}

void MapInfo::update()
{
	collision->update();
}

void MapInfo::setPlaying(bool isPlaying)
{
	this->isPlaying = isPlaying;
}

void MapInfo::addActor(Actor * actor)
{
	actors.pushBack(actor);
	world->addActor(actor);
}

MapInfo::~MapInfo()
{
	int m = mapSize.height;
	for (int i = 0; i < m; ++i)
	{
		delete tiles[i];
	}
	delete tiles;
}

//CollisionMap

CollisionMap * CollisionMap::create(MapInfo * info)
{
	CollisionMap *ret = new CollisionMap();
	if (ret && ret->init(info))
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

void CollisionMap::fillTiles(int x, int y, int x1, int y1, bool val)
{
	for (int i = y; i <= y1; ++i)
	for (int j = x; j <= x1; ++j)
	{
		map[i][j] = val;
	}
}

bool CollisionMap::init(MapInfo * info)
{
	this->level = info;

	int m = level->mapSize.height * 4;
	int n = level->mapSize.width * 4;

	map = new bool*[m];
	for (int i = 0; i < m; i += 4)
	{
		map[i] = new bool[n];
		map[i+1] = new bool[n];
		map[i+2] = new bool[n];
		map[i+3] = new bool[n];
		for (int j = 0; j < n; j += 4)
		{
			if (level->tiles[i / 4][j / 4]->getType() == TILE_GROUND)
			{
				fillTiles(j, i, j + 3, i + 3, true);
			}
			else
				fillTiles(j, i, j + 3, i + 3, false);

			if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_EAST)
			{
				fillTiles(j, i, j + 2, i + 3, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_WEST)
			{
				fillTiles(j + 1, i, j + 3, i + 3, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_NORTH)
			{
				fillTiles(j, i + 1, j + 3, i + 3, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_SOUTH)
			{
				fillTiles(j, i, j + 3, i + 2, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_CORNER_DOWN)
			{
				fillTiles(j + 1, i, j + 3, i + 2, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_CORNER_UP)
			{
				fillTiles(j, i + 1, j + 2, i + 3, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_CORNER_LEFT)
			{
				fillTiles(j + 1, i + 1, j + 3, i + 3, true);
			}
			else if (level->tiles[i / 4][j / 4]->getType() == TILE_WALL_CORNER_RIGHT)
			{
				fillTiles(j, i, j + 2, i + 2, true);
			}
		}
	}


	saveToFile("mapc.txt");
	return true;
}

void CollisionMap::saveToFile(std::string fileName)
{
	int m = level->mapSize.height * 4;
	int n = level->mapSize.width * 4;

	FILE *fp = fopen(fileName.c_str(), "w");

	if (!fp)
	{
		CCLOG("can not create file %s", fileName.c_str());
		return;
	}

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
			std::fputc(48 + map[i][j], fp);
		std::fputc('\n', fp);
	}
	fclose(fp);
}

bool CollisionMap::isWalkable(Vec2i point)
{
	return map[point.y][point.x];
}

bool CollisionMap::isWalkable(Vec2 point)
{
	return map[(int)point.y][(int)point.x];
}

bool CollisionMap::isWalkable(Vec2i point, int radius)
{
	return map[point.y][point.x];
}
bool CollisionMap::isWalkable(Vec2 point, int radius)
{
	return map[(int)point.y][(int)point.x];
}

void CollisionMap::setCollision(Vec2i point, bool isWalkable)
{
	map[point.y][point.x] = isWalkable;
}

void CollisionMap::setCollision(Vec2 point, bool isWalkable)
{
	map[(int)point.y][(int)point.x] = isWalkable;
}

void CollisionMap::setCollision(Vec2 point, int radius, bool isWalkable)
{/*
	int x0 = point.x;
	int y0 = point.y;
	int x = radius / 100;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;
	while (x >= y)
	{
	for (int i = x0 - x; i <= x0 + x; i++)
	{
	map[y0 + y][i] = isWalkable;
	map[y0 - y][i] = isWalkable;
	}
	for (int i = x0 - y; i <= x0 + y; i++)
	{
	map[y0 + x][i] = isWalkable;
	map[y0 - x][i] = isWalkable;
	}

	y++;
	radiusError += yChange;
	yChange += 2;
	if (((radiusError << 1) + xChange) > 0)
	{
	x--;
	radiusError += xChange;
	xChange += 2;
	}
	}
	//*/map[(int)point.y][(int)point.x] = isWalkable;
}

CollisionMap::~CollisionMap()
{
	int m = level->mapSize.height * 4;
	for (int i = 0; i < m; ++i)
	{
		delete map[i];
	}
	delete map;
}

void CollisionMap::update()
{
	for (int i = level->actors.size() - 1; i >= 0; --i)
	if (level->actors.at(i)->isSleeping() == false)
	{
	}
}