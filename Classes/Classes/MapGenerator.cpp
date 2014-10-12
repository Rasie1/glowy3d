#include "MapGenerator.h"

USING_NS_CC;

//MapGenerator

MapGenerator * MapGenerator::create(Size size, MapInfo * map)
{
	MapGenerator * ret = new MapGenerator();
	if (ret && ret->init(size, map))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool MapGenerator::init(Size size, MapInfo * sender)
{
	mapSize = size;
	map = sender;

	return 1;
}

void MapGenerator::generate()
{
	auto tileset = (TilesetGenerator::create())->getTileset();

	for (int i = 0; i < mapSize.width; ++i)
	for (int j = 0; j < mapSize.height; ++j)
	{
		map->tiles[j][i] = TileInfo::create(tileset->getByType(TILE_NONE), TILE_NONE);
	}
	map->tiles[(int)map->playerStart.y][(int)map->playerStart.x] = TileInfo::create(tileset->getByType(TILE_GROUND), TILE_GROUND);
	graph = RoomMapNode::create(map->playerStart - Vec2(3, 3), map->playerStart - Vec2(3, 3));
	graph->apply(map);
}

MapNode * MapGenerator::getRandomNode()
{
	return openNodes.getRandomObject();
}

void MapGenerator::addOpenNode(MapNode * node)
{
	openNodes.pushBack(node);
}

//DungeonMapGenerator

void DungeonMapGenerator::generate()
{
	//std::fill(&map->tiles[0][0], &map->tiles[0][0] + sizeof(map->tiles), 0);

	auto tileset = (TilesetGenerator::create())->getTileset();

	for (int i = 0; i < mapSize.width; ++i)
	for (int j = 0; j < mapSize.height; ++j)
	{
		map->tiles[j][i] = TileInfo::create(tileset->getByType(TILE_NONE), TILE_NONE);
	}
	
	
	
	
	map->tiles[(int)map->playerStart.y][(int)map->playerStart.x] = TileInfo::create(tileset->getByType(TILE_GROUND), TILE_GROUND);

	graph = RoomMapNode::create(map->playerStart - Vec2(3, 3), map->playerStart + Vec2(3, 3));
	graph->apply(map);

	powerPoints = kDefaultDungeonPowerPoints;
	srand(time(0));

	while (powerPoints > 0)
	{
		if (openNodes.size() == 0)
			break;
		auto randomIt = rand() % openNodes.size();
		WallMapNode * wall = (WallMapNode*)(openNodes.at(randomIt));

		openNodes.erase(randomIt);
		wall->use();

		int minDist = 5;
		int maxDistOffset = 11;
		int roomOffset = minDist + rand() % maxDistOffset;

		int minBoundaryDist = 2;
		int maxBoundaryDist = roomOffset / 2;

		Vec2 position = wall->getWallEnd().getMidpoint(wall->getWallStart());
		if (wall->getDirection() == DIRECTION_N)
		{
			position -= Vec2(0, roomOffset);
		}
		else if (wall->getDirection() == DIRECTION_E)
		{
			position += Vec2(roomOffset, 0);
		}

		else if (wall->getDirection() == DIRECTION_S)
		{
			position += Vec2(0, roomOffset);
		}
		else if (wall->getDirection() == DIRECTION_W)
		{
			position -= Vec2(roomOffset, 0);
		}

		maxBoundaryDist++;
		int n = position.x + maxBoundaryDist;
		int m = position.y + maxBoundaryDist;
		int startx = position.x - maxBoundaryDist;
		int starty = position.y - maxBoundaryDist;
		maxBoundaryDist--;
		if (starty > 0
			&& startx > 0
			&& m + 1 < map->mapSize.height
			&& n + 1< map->mapSize.width
			&& map->tiles[m][n]->getType() == TILE_NONE
			&& map->tiles[starty][n]->getType() == TILE_NONE
			&& map->tiles[m][startx]->getType() == TILE_NONE
			&& map->tiles[starty][startx]->getType() == TILE_NONE
			&& map->tiles[m+1][n+1]->getType() == TILE_NONE
			&& map->tiles[starty-1][n+1]->getType() == TILE_NONE
			&& map->tiles[m + 1][startx - 1]->getType() == TILE_NONE
			&& map->tiles[starty - 1][startx - 1]->getType() == TILE_NONE
			&& map->tiles[(int)position.y][n]->getType() == TILE_NONE
			&& map->tiles[m][(int)position.x]->getType() == TILE_NONE
			&& map->tiles[(int)position.y][startx]->getType() == TILE_NONE
			&& map->tiles[starty][(int)position.x]->getType() == TILE_NONE
			&& map->tiles[(int)position.y][n+1]->getType() == TILE_NONE
			&& map->tiles[m+1][(int)position.x]->getType() == TILE_NONE
			&& map->tiles[(int)position.y][startx-1]->getType() == TILE_NONE
			&& map->tiles[starty - 1][(int)position.x]->getType() == TILE_NONE
			&& map->tiles[(int)position.y][(int)position.x]->getType() == TILE_NONE
			&& map->tiles[((int)wall->getWallStart().y + starty) / 2][((int)wall->getWallStart().x + startx) / 2]->getType() == TILE_NONE
			&& map->tiles[((int)wall->getWallEnd().y + m) / 2][((int)wall->getWallEnd().x + n) / 2]->getType() == TILE_NONE)
		{
			Vec2 roomCorner1 = position - Vec2(std::max(minBoundaryDist, rand() % maxBoundaryDist), std::max(minBoundaryDist, rand() % maxBoundaryDist));
			Vec2 roomCorner2 = position + Vec2(std::max(minBoundaryDist, rand() % maxBoundaryDist), std::max(minBoundaryDist, rand() % maxBoundaryDist));
			RoomMapNode * room;
			CorridorMapNode * corr;
			
			int corrWidth = rand() % 2 ? 2 : (rand() % 2 + 2);
			Vec2 corrCorner1, corrCorner2;
			if (wall->getDirection() == DIRECTION_N || wall->getDirection() == DIRECTION_S)
			{
				corrCorner1 = Vec2(std::max(wall->getWallStart().x + 1, roomCorner1.x + 1), 0) + Vec2(rand() % std::max(1, (int)(wall->getWallEnd().x - wall->getWallStart().x - corrWidth)), (wall->getDirection() == DIRECTION_N) ? roomCorner2.y + 1 : wall->getWallStart().y + 1);

				while (corrCorner1.x + corrWidth > wall->getWallEnd().x)
					corrWidth--;

				corrCorner2 = Vec2(corrCorner1.x + corrWidth, (wall->getDirection() == DIRECTION_N) ? wall->getWallStart().y - 1 : roomCorner1.y - 1);
				corr = CorridorMapNode::create(corrCorner1, corrCorner2, wall->getDirection());
				wall->addEntrance(corrCorner1.x, corrCorner2.x); 
				room = RoomMapNode::create(roomCorner1, roomCorner2, wall->getDirection(), corrCorner1.x, corrCorner2.x);
			}
			else
			{
				corrCorner1 = Vec2((wall->getDirection() == DIRECTION_W) ? roomCorner2.x + 1 : wall->getWallStart().x + 1, std::max(wall->getWallStart().y + 1, roomCorner1.y + 1));
				while (corrCorner1.y + corrWidth > wall->getWallEnd().y)
					corrWidth--;
				corrCorner2 = Vec2((wall->getDirection() == DIRECTION_E) ? roomCorner1.x - 1 : wall->getWallStart().x - 1, corrCorner1.y + corrWidth + rand() % (std::max(1, (int)(std::min(wall->getWallEnd().y, roomCorner2.y) - corrCorner1.y - 1))));
				corr = CorridorMapNode::create(corrCorner1, corrCorner2, wall->getDirection());
				wall->addEntrance(corrCorner1.y, corrCorner2.y);
				room = RoomMapNode::create(roomCorner1, roomCorner2, wall->getDirection(), corrCorner1.y, corrCorner2.y);
			}

			wall->apply(map); //warning for overlapping prev changes?
			room->apply(map);
			corr->apply(map);
			powerPoints -= kDefaultDungeonRoomCost;
		}
	}
	
	
	return;
}

bool DungeonMapGenerator::init(Size size, MapInfo * sender)
{
	mapSize = size;
	map = sender;

	return 1;
}

DungeonMapGenerator * DungeonMapGenerator::create(Size size, MapInfo * map)
{
	DungeonMapGenerator * ret = new DungeonMapGenerator();
	if (ret && ret->init(size, map))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}