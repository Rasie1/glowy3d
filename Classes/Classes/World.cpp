#include "World.h"

//TileSprite

TileSprite * TileSprite::create(Texture2D * tex, const Vec2& pos)
{
	TileSprite * ret = new TileSprite();
	if (ret && ret->init(tex, pos))
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

TileSprite * TileSprite::create(TileInfo * tile, const Vec2& pos)
{
	TileSprite * ret = new TileSprite();

	if (ret && ret->init(tile->getTexture(), pos))
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

bool TileSprite::init(Texture2D * tex, const Vec2& globalPos)
{
	Sprite::initWithTexture(tex);
	//Sprite::init();
	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setPosition(globalPos);

	return true;
}

//World

bool World::init(MapInfo * currentMap)
{
	Layer::init();
	this->map = currentMap;
	this->setAnchorPoint(map->playerStart);

	Size screenSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(screenSize.width / 2, screenSize.height / 2);

	//Tile Sprites and actors init section
	tiles = new TileSprite**[(int)map->mapSize.height];
	for (int i = 0; i < map->mapSize.height; ++i)
	{
		tiles[i] = new TileSprite*[(int)map->mapSize.width];
		for (int j = 0; j < map->mapSize.width; ++j)
		{
			if (map->tiles[i][j]->getType() != TILE_NONE)
			{
				tiles[i][j] = TileSprite::create(map->tiles[i][j], tileToCoord(Vec2(j * 4 - 1, i * 4 + 5), map->tileSize / 4));
				this->addChild(tiles[i][j], i - j);
				//this->tiles[i][j]->setVisible(false);
			}

		}
	}

	//Init actors
	for (int i = map->actors.size() - 1; i >= 0; --i)
	{
		addActor(map->actors.at(i));
	}

	//Camera init section
	_spritesVisibleRadiusSquared = Director::getInstance()->getVisibleSize().width / map->tileSize * 2;
	_spritesInvisibleRadius = _spritesVisibleRadiusSquared + 3;
	_spritesVisibleRadiusSquared *= _spritesVisibleRadiusSquared + kVisibleSpritesRange;
	_cameraCenterPosition = this->getPosition();
	_renderingCenterPosition = Vec2(900000, 9999990);
	//updateSpritesVisibility();

	player = Player::create(tileToCoord(map->playerStart, map->tileSize), map);
	map->player = player;
	addChild(player, 999);

	this->setPosition(center - player->getPosition());
	this->setAnchorPoint(Vec2(0, 0));

	zoomFactor = 1.00f;
	
	return true;
}

Vec2 World::findCollision(Vec2 from, const Vec2& to, const Vec2& step)
{
	float speed = step.getLength();
	for (float length = from.getDistance(to); length > 0; from += step, length -= speed)
	{
		Vec2 check = coordToTile(from, map->tileSize);
		if ((int)check.y >= 0 && (int)check.x >= 0 && (int)check.x < map->mapSize.width && (int)check.y < map->mapSize.height) //заменить это нормальной функцией
		if (map->tiles[(int)check.y][(int)check.x]->isWalkable())
			return from;
	}
	return to;
}

Vec2 World::cutIfCollided(const Vec2& from, const Vec2& delta)
{
	Vec2 check = coordToTile(from + delta, map->tileSize);
	if ((int)check.y >= 0 && (int)check.x >= 0 && (int)check.x < map->mapSize.width && (int)check.y < map->mapSize.height) //заменить это нормальной функцией
	if (!map->tiles[(int)check.y][(int)check.x]->isWalkable())
		return Vec2(0, 0);
	return delta;
}

World * World::create(MapInfo * currentMap)
{
	World *ret = new World();
	if (ret && ret->init(currentMap))
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


void World::scroll()
{
	//this->setPosition(this->getPosition() + delta * zoomFactor);
	//this->setPosition(this->getPosition() + (player->getPosition() - getPosition()) * zoomFactor);
	Size screenSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(screenSize.width / 2, screenSize.height / 2);
	setPosition(center - player->getPosition() * zoomFactor);
	_cameraCenterPosition = this->getPosition();
}

void World::updateFrame(float timeCoefficient)
{
	player->act(timeCoefficient);
	for (int i = map->actors.size() - 1; i >= 0; --i)
	if (!map->actors.at(i)->isSleeping())
			map->actors.at(i)->act(timeCoefficient);
	scroll();
}

void World::updateTenth()
{
	player->actTenth();
	for (int i = map->actors.size() - 1; i >= 0; --i)
	if (!map->actors.at(i)->isSleeping())
		map->actors.at(i)->actTenth();
}

void World::updateSecond()
{
	updateSpritesVisibility();
	updateLocalActorsVector();
}

void World::updateSpritesVisibility()
{
	return;
	//не проверять, если еще не сдвинулись
	if (abs(_cameraCenterPosition.x - _renderingCenterPosition.x) < map->tileSize && abs(_cameraCenterPosition.y - _renderingCenterPosition.y) < map->tileSize) //можно заменить функцией
		return;
	//обновить текущую позицию
	_renderingCenterPosition = _cameraCenterPosition;

	const Vec2 x_renderingCenterPosition = _renderingCenterPosition - Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	Vec2 tileCenter = coordToTile(x_renderingCenterPosition, map->tileSize);

	int _x = tileCenter.x;
	int _y = tileCenter.y;
	int wx = map->mapSize.width;
	int wy = map->mapSize.height;
	for (int i = _y - _spritesInvisibleRadius; i < _y + _spritesInvisibleRadius; ++i)
	for (int j = _x - _spritesInvisibleRadius; j < _x + _spritesInvisibleRadius; ++j)
	{
		if (i >= 0 && j >= 0 && j < wx && i < wy && map->tiles[i][j]->getType() != TILE_NONE)
		{
			int ci = i - _y;
			int cj = j - _x;
			if (ci*ci + cj*cj < _spritesVisibleRadiusSquared)
				this->tiles[i][j]->setVisible(true);
			else
				this->tiles[i][j]->setVisible(false);
		}
	}
}

void World::updateLocalActorsVector()
{
	for (int i = map->actors.size() - 1; i >= 0; --i)
	{
		if (map->actors.at(i)->getPosition().getDistanceSq(player->getPosition()) > kActorsSleepRadius)
		{
			map->actors.at(i)->setSleeping(true);
			//overlay->remove(map->actors.at(i)->onMouseDown);
		}
		else
		{
			map->actors.at(i)->setSleeping(false);
			if (map->actors.at(i)->isSelectable() && map->actors.at(i)->onMouseDown == nullptr)
			{
				auto part = InterfacePartActor::create(map->actors.at(i));
				overlay->add(part);
				map->actors.at(i)->onMouseDown = part;
			}
			//localActors.pushBack(actors.at(i));
		}
	}
}

void World::zoom(float k)
{
	//Vec2 mapSize = map->mapSize * map->tileSize * zoomFactor;
	//setAnchorPoint(getAnchorPoint() * k);
	setScale(k);
	_renderingCenterPosition *= k;
	_cameraCenterPosition *= k;

	//Correct the position of camera
	//Vec2 halfMap = map->mapSize * map->tileSize / 2 * zoomFactor;
	//setPosition((getPosition() - halfMap) * k + halfMap);
	Size screenSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(screenSize.width / 2, screenSize.height / 2);
	setPosition(center - player->getPosition() * k);
	zoomFactor = k;
}

void World::zoomIn()
{
	zoomFactor += float(kZoomSpeed) / 100;
	zoom(zoomFactor);
}

void World::zoomOut()
{
	zoomFactor -= float(kZoomSpeed) / 100;
	zoom(zoomFactor);
}

void World::addActor(Actor * actor)
{
	this->addChild(actor, 999);
	actor->setVisible(true);
	actor->setAnchorPoint(Vec2(0.5, 0.5));
	//actors.back()->getTexture()->setAliasTexParameters();
}

//WorldManager

bool WorldManager::init()
{
	map = MapInfo::create(MAPTYPE_DUNGEON, Size(kDefaultMapSize, kDefaultMapSize));
	map->retain();
	world = World::create(map);
	//world->retain();
	map->world = world;
	parent->addChild(world);
	initInterface();

	return true;
}

World * WorldManager::getWorld()
{
	return world;
}


void WorldManager::nextWorld()
{
	
}
 
void WorldManager::finish()
{
	parent->removeChild(world);
	parent->removeChild(overlay);
	map->release();
	init();
}

void WorldManager::initInterface()
{
	overlay = InterfaceBase::create(world->map);
	world->overlay = overlay;
	parent->addChild(overlay, 9000);
}