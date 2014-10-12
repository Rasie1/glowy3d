#include "MapPath.h"

Pathfinder * Pathfinder::create(Creature * creature)
{
	Pathfinder * ref = new Pathfinder();
	if (ref && ref->init(creature))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool Pathfinder::init(Creature * creature)
{
	this->creature = creature;
	m_isMoving = false;

	walk = creature->map->collision->map;

	return true;
}

void Pathfinder::setDestination(const Vec2& to)
{
	m_target = to;
	m_isMoving = true;
	findPath();
}

bool Pathfinder::isMoving()
{
	return m_isMoving;
}

void Pathfinder::findPath()
{
	m_isMoving = true;
	/*
	//At first, check if it's already found some path to the point
	if (!finalPath.empty() && m_target - finalPath.back() < Vec2(10, 10))
	return; //It's the same path
	*/
	Vec2 _from;
	/*
	//Now check if we are already moving towards the target
	if (!finalPath.empty())
	{
	auto it = finalPath.end(); //Start from the last target
	while (--it != finalPath.begin())
	{
	if (rayTrace(m_target, *it, creature->map)) //If the point is not visible
	{											//We should find path to latest
	it++; //Switch to last visible point	//Visible point
	if (it != finalPath.end())
	{
	it++;
	while (it++ != finalPath.end()) //Pop all points after last visible
	finalPath.pop_back();
	_from = coordToTile(finalPath.back(), creature->map->tileSize) * 4;
	}
	else //No visible points at all, we should find path from a scratch
	{
	finalPath.clear();*/
	_from = coordToTile(creature->getPosition(), creature->map->tileSize) * 4;
	/*}
	break;
	}
	}
	}*/

	//Now find the remaining path with A Star

	Vec2 _target = coordToTile(m_target, creature->map->tileSize) * 4;
	Vec2i fr = Vec2i(_from.x, _from.y - 4);
	//Vec2 oldTo = to;
	Vec2i to = Vec2i(_target.x, _target.y - 4);
	m_to = &to;

	open.push_back(Vec2iv(fr, cost(fr)));
	lengths[fr] = 0;
	parents[fr] = fr;

	int maxOperations = kMaxPathfindingOperations;

	while (maxOperations)
	{
		if (open.empty())
			break;
		Vec2i point = Vec2i(open.front());
		Vec2i cur = Vec2i(point);
		pop_heap(open.begin(), open.end());
		open.pop_back();
		closed.insert(point);
		inOpen[point] = false;
		if (point.x < 1 || point.y < 1 || point.x > creature->map->mapSize.width * 4 - 5 || point.y > creature->map->mapSize.height * 4 - 5)
			continue;

		if (point.compare(Vec2i(to.x, to.y))) //If path is found
		{
			auto lastVisiblePoint = point;
			finalPath.push_front(tileToCoord(Vec2(point.x, point.y), creature->map->tileSize / 4));
			point = parents[point];
			while (!point.compare(fr))
			{//*
				if (rayTrace(lastVisiblePoint, point, creature->map)) //We need to cut unnecessary path points
				{											//to prevent "tileness" of movement
				finalPath.push_front(tileToCoord(Vec2(lastVisiblePoint.x, lastVisiblePoint.y), creature->map->tileSize / 4));
				finalPath.push_front(tileToCoord(Vec2(point.x, point.y), creature->map->tileSize / 4));
				lastVisiblePoint = point;
				}//*/finalPath.push_front(tileToCoord(Vec2(point.x, point.y), creature->map->tileSize / 4));
			point = parents[point];
			}

			break;
		}
		//Check and add to open
		point.x += 1;
		processPoint(point, cur);
		point.y += 1;
		processPoint(point, cur);
		point.x -= 1;
		processPoint(point, cur);
		point.x -= 1;
		processPoint(point, cur);
		point.y -= 1;
		processPoint(point, cur);
		point.y -= 1;
		processPoint(point, cur);
		point.x += 1;
		processPoint(point, cur);
		point.x += 1;
		processPoint(point, cur);

		maxOperations--;
	}

	open.clear();
	inOpen.clear();
	closed.clear();
	parents.clear();
	lengths.clear();
}

Pathfinder::~Pathfinder()
{
}

Vec2 Pathfinder::getNextPoint()
{
	if (finalPath.empty())
	{
		m_isMoving = false;
		return creature->getPosition();
	}
	auto point = finalPath.front();
	finalPath.pop_front();
	return point;
}

int Pathfinder::cost(const Vec2i& point)
{
	return point.getDistance(*m_to) + lengths[point];
}

void Pathfinder::processPoint(const Vec2i& point, const Vec2i& parent)
{
	if (closed.find(point) != closed.end())
		return;

	bool notCorner = true;/*
	if (point.x == parent.x - 1)
	{
	if (point.y == parent.y - 1)
	{
	if (walk[parent.y][parent.x - 1] == false
	|| walk[parent.y - 1][parent.x] == false)
	notCorner = false;
	}
	else if (point.y == parent.y + 1)
	{
	if (walk[parent.y][parent.x - 1] == false
	|| walk[parent.y + 1][parent.x] == false)
	notCorner = false;
	}
	}
	else if (point.x == parent.x + 1)
	{
	if (point.y == parent.y - 1)
	{
	if (walk[parent.y][parent.x + 1] == false
	|| walk[parent.y - 1][parent.x] == false)
	notCorner = false;
	}
	else if (point.y == parent.y + 1)
	{
	if (walk[parent.y][parent.x + 1] == false
	|| walk[parent.y + 1][parent.x] == false)
	notCorner = false;
	}
	}*/

	if (walk[point.y][point.x] && notCorner)
	{
		//Check if it's already in open list
		if (inOpen[point])
		{
			int moveLength = ((point.x - parent.x != 0) ^ (point.y - parent.y != 0)) ? 5 : 7;
			newLength = lengths[parent] + moveLength;
			if (newLength < lengths[point])
			{
				parents[point] = parent;
				lengths[point] = newLength;

				n = open.size();

				for (int i = 0; i < n; ++i)
				if (open[i].compare(point))
				{
					open[i].val = cost(point);
					break;
				}

				std::make_heap(open.begin(), open.end());
			}
		}
		else
		{
			parents[point] = parent;
			lengths[point] = lengths[parent] + ((point.x - parent.x != 0) ^ (point.y - parent.y != 0)) ? 5 : 7;;
			open.push_back(Vec2iv(point, cost(point)));
			std::push_heap(open.begin(), open.end());
			inOpen[point] = true;
		}
	}
	else
	{
		closed.insert(point);
	}
}

//MapPath

MapPath * MapPath::create(Creature * creature)
{
	MapPath * ref = new MapPath();
	if (ref && ref->init(creature))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool MapPath::init(Creature * creature)
{
	map = creature->map;
	walk = map->collision->map;
	this->creature = creature;
	this->maxOperations = 900;
	tileSize4 = map->tileSize / 4;
	currentMovementTarget = path.end();
	isGettingToThePoint = true;
	isDone = true;

	return true;
}

void MapPath::setDestination(const Vec2& target)
{
	this->target = target;
	isDone = true;
	isGettingToThePoint = true; //remove this thing
	currentMovementTarget = path.begin();
	findPath();
}

void MapPath::findPath()
{
	if (!isDone)
		return;

	isDone = false;
	isGettingToThePoint = true;
	from = creature->getPosition();
	Vec2 _from;

	//At first, check if it's already found some path to the point
	//Now check if we are already moving towards the target
	/*
	if (!path.empty())
	{
		auto it = path.end(); //Start from the last target
		while (--it != path.begin())
		{
			if (rayTrace(coordToTile(target, map->tileSize * 4), coordToTile(*it, map->tileSize * 4), creature->map)) //If the point is not visible
			{											//We should find path to latest
				it++; //Switch to last visible point	//Visible point
				if (it != path.end())
				{
					it++;
					while (it++ != path.end()) //Pop all points after last visible
						path.pop_back();
					_from = coordToTile(path.back(), creature->map->tileSize) * 4;
				}
				else //No visible points at all, we should find path from a scratch
				{
					path.clear();
					_from = coordToTile(creature->getPosition(), creature->map->tileSize) * 4;

				}
				break;
			}
		}
	}
	else//*/
	{
		_from = coordToTile(from, map->tileSize) * 4;

		//path.clear();
	}
	
	//Find tiled path with A*
	Vec2 _target = coordToTile(target, map->tileSize) * 4;
	//Vec2 _from = coordToTile(from, map->tileSize) * 4;
	Vec2i fr = Vec2i(_from.x, _from.y);
	oldTo = to;
	to = Vec2(_target.x, _target.y);

	//Leave path the same if we already found it in previous take
	if (to == oldTo)
	{
		isDone = true;
		return;
	}
	path.clear();

	//If clicked at unwalkable tile, change target to closes walkable tile
	checkAndFixTarget();
	//isGettingToThePoint = false;

	open.push_back(Vec2iv(fr, cost(fr)));
	lengths[fr] = 0;
	parents[fr] = fr;

	maxOperations = kMaxPathfindingOperations;

	/*
	std::string spath = "mappath.txt";
	FILE *fp = fopen(spath.c_str(), "w");

	if (!fp)
	{
		CCLOG("can not create file %s", spath.c_str());
		walk[-1][-1] = 3;
	}
	*/

	while (maxOperations)
	{

		/*for (int i = 0; i < map->mapSize.height * 4; ++i)
		{
			for (int j = 0; j < map->mapSize.width * 4; ++j)
			if (inOpen[Vec2i(j, i)] == true)
			{
				std::fputc('o', fp);
			}
			else if (closed.find(Vec2i(j,i)) != closed.end())
			{
				std::fputc('x', fp);
			}
			else
				std::fputc(48 + walk[i][j], fp);
			std::fputc('\n', fp);
		}

		std::fputc('\n', fp);

		std::fputc('\n', fp);

		*/

		if (open.empty())
			break;
		Vec2i point = Vec2i(open.front());
		Vec2i cur = Vec2i(point);
		pop_heap(open.begin(), open.end());
		open.pop_back();
		closed.insert(point);
		inOpen[point] = false;
		if (point.x < 1 || point.y < 1 || point.x > map->mapSize.width * 4 - 5 || point.y > map->mapSize.height * 4 - 5)
			continue;

		if (point.compare(Vec2i(to.x, to.y))) //If path is found
		{
			auto lastVisiblePoint = point;
			path.push_front(tileToCoord(Vec2(point.x, point.y), map->tileSize / 4));
			point = parents[point];
			//std::map<Vec2i, bool> shittyPath;
			
			while (!point.compare(fr))
			{//*
				if (rayTrace(lastVisiblePoint, point, map)) //We need to cut unnecessary path points
				{											//to prevent "tileness" of movement
				//path.push_front(tileToCoord(Vec2(lastVisiblePoint.x, lastVisiblePoint.y), map->tileSize / 4));
				path.push_front(tileToCoord(Vec2(point.x, point.y), map->tileSize / 4));
				lastVisiblePoint = point;
				}//*/path.push_front(tileToCoord(Vec2(point.x, point.y), map->tileSize / 4));
			point = parents[point];
			//shittyPath[point] = true;
			}
			currentMovementTarget = path.begin();

			/*
			for (int i = 0; i < map->mapSize.height * 4; ++i)
			{
				for (int j = 0; j < map->mapSize.width * 4; ++j)
				if (inOpen[Vec2i(j, i)] == true)
				{
					std::fputc('X', fp);
				}
				else
					std::fputc(48 + walk[i][j], fp);
				std::fputc('\n', fp);
			}*/

			break;
		}
		//Check and add to open
		point.x += 1;
		processPoint(point, cur);
		point.y += 1;
		processPoint(point, cur);
		point.x -= 1;
		processPoint(point, cur);
		point.x -= 1;
		processPoint(point, cur);
		point.y -= 1;
		processPoint(point, cur);
		point.y -= 1;
		processPoint(point, cur);
		point.x += 1;
		processPoint(point, cur);
		point.x += 1;
		processPoint(point, cur);

		maxOperations--;
	}

	//Cut unnecessary nodes with raytracing
	/*
	auto point = path.begin();
	auto point2 = path.begin();
	point2++;
	while (point2 != path.end() && *point2 != target)
	{
	if (rayTrace(*point, *point2, map))
	{
	point = point2++;
	}
	else
	{
	point2 = path.erase(point2);
	point2++;
	}
	}
	*/
	//End
	//fclose(fp);
	open.clear();
	inOpen.clear();
	closed.clear();
	parents.clear();
	lengths.clear();
	isDone = true;
}

Vec2 MapPath::back()
{
	return (*currentMovementTarget);
}

void MapPath::next()
{
	currentMovementTarget++;
}

bool MapPath::isEmpty()
{
	return path.size() == 0 || currentMovementTarget == path.end();
}

void MapPath::processPoint(const Vec2i& point, const Vec2i& parent)
{
	if (closed.find(point) != closed.end())
		return;

	bool notCorner = true;
	/*
	if (point.x == parent.x - 1)
	{
		if (point.y == parent.y - 1)
		{
			if (map->collision->map[parent.y][parent.x - 1] == false
				|| map->collision->map[parent.y - 1][parent.x] == false)
				notCorner = false;
		}
		else if (point.y == parent.y + 1)
		{
			if (map->collision->map[parent.y][parent.x - 1] == false
				|| map->collision->map[parent.y + 1][parent.x] == false)
				notCorner = false;
		}
	}
	else if (point.x == parent.x + 1)
	{
		if (point.y == parent.y - 1)
		{
			if (map->collision->map[parent.y][parent.x + 1] == false
				|| map->collision->map[parent.y - 1][parent.x] == false)
				notCorner = false;
		}
		else if (point.y == parent.y + 1)
		{
			if (map->collision->map[parent.y][parent.x + 1] == false
				|| map->collision->map[parent.y + 1][parent.x] == false)
				notCorner = false;
		}
	}
	//*/
	if (map->collision->map[point.y][point.x] && notCorner)
	{
		//Check if it's already in open list
		if (inOpen[point])
		{
			int moveLength = ((point.x - parent.x != 0) ^ (point.y - parent.y != 0)) ? 5 : 7;
			newLength = lengths[parent] + moveLength;
			if (newLength < lengths[point])
			{
				parents[point] = parent;
				lengths[point] = newLength;

				n = open.size();

				for (int i = 0; i < n; ++i)
				if (open[i].compare(point))
				{
					open[i].val = cost(point);
					break;
				}

				std::make_heap(open.begin(), open.end());
			}
		}
		else
		{
			parents[point] = parent;
			lengths[point] = lengths[parent] + ((point.x - parent.x != 0) ^ (point.y - parent.y != 0)) ? 5 : 7;;
			open.push_back(Vec2iv(point, cost(point)));
			std::push_heap(open.begin(), open.end());
			inOpen[point] = true;
		}
	}
	else
	{
		closed.insert(point);
	}
}

int MapPath::cost(const Vec2i& point)
{
	return point.getDistance(Vec2i(to.x, to.y)) + lengths[point];
}

void MapPath::updateOpenHeap(int i, int value)
{
	int size = open.size();
	open[i].val = value;

	while (i != 0 && value < open[i / 2].val)
	{
		std::swap(open[i / 2], open[i]);
		i /= 2;
	}
}

void MapPath::checkAndFixTarget()
{
	if (map->collision->isWalkable(to))
		return;
	//If target is an unwalkable tile, find closest
	//walkable tile with Dijkstra's alghorithm

	open2.push_back(Vec2iv(Vec2i(to.x, to.y), 0));
	Vec2i point;

	while (true)
	{
		point = open2.front().vec;
		std::pop_heap(open2.begin(), open2.end());
		open2.pop_back();
		Vec2i cur = Vec2i(point);
		closed2.insert(point);
		inOpen2[point] = false;
		if (point.x < 1 || point.y < 1 || point.x > map->mapSize.width * 4 - 5 || point.y > map->mapSize.height * 4 - 5)
			continue;

		if (map->collision->isWalkable(point))
		{
			to = point;
			break;
		}

		point.x += 1;
		processPointInTargetFixing(point, cur);
		point.y += 1;
		processPointInTargetFixing(point, cur);
		point.x -= 1;
		processPointInTargetFixing(point, cur);
		point.x -= 1;
		processPointInTargetFixing(point, cur);
		point.y -= 1;
		processPointInTargetFixing(point, cur);
		point.y -= 1;
		processPointInTargetFixing(point, cur);
		point.x += 1;
		processPointInTargetFixing(point, cur);
		point.x += 1;
		processPointInTargetFixing(point, cur);
	}

	open2.clear();
	inOpen2.clear();
	closed2.clear();
	parents2.clear();
	lengths2.clear();
}

void MapPath::processPointInTargetFixing(const Vec2i& point, const Vec2i& parent) //TODO optimize and
{                               //remove unnecessary containers for Dijkstra's
	if (closed2.find(point) != closed2.end())
		return;
	//Check if it's already in open list
	if (inOpen2[point])
	{
		int moveLength = ((point.x - parent.x != 0) ^ (point.y - parent.y != 0)) ? 5 : 7;
		newLength = lengths2[parent] + moveLength;
		if (newLength < lengths2[point])
		{
			parents2[point] = parent;
			lengths2[point] = newLength;

			n = open2.size();

			for (int i = 0; i < n; ++i)
			if (open2[i].compare(point))
			{
				open2[i].val = newLength;
				break;
			}

			std::make_heap(open2.begin(), open2.end());
		}
	}
	else
	{
		parents2[point] = parent;
		lengths2[point] = lengths2[parent] + ((point.x - parent.x != 0) ^ (point.y - parent.y != 0)) ? 5 : 7;;
		open2.push_back(Vec2iv(point, lengths2[point]));
		std::push_heap(open2.begin(), open2.end());
		inOpen2[point] = true;
	}
}