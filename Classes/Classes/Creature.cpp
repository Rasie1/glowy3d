#include "Creature.h"

Creature* Creature::create(const Vec2& pos, MapInfo * map)
{
	auto ref = new (std::nothrow) Creature();
	if (ref && ref->init(pos, map))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool Creature::init(const Vec2& pos, MapInfo * map)
{
	Actor::init(pos, map);
	setTexture("blank.png");
	//setTextureRect(Rect(0, 0, 100, 100));
	//setColor(Color3B(255, 100, 100));
	setAnchorPoint(Vec2(0.5, 0.5));
	speed = 1;
	moveVector = Vec2(0, 0);
	health = 40;
	radius = 128;
	selectable = true;
	sleeping = true;
	onMouseDown = nullptr;
	attackOnMoveDone = true;
	isMoving = true;
	shouldUpdatePath = true;
	attackRange = 20000;
	movingQueue = MapPath::create(this);
	movingQueue->retain();
	teamNumber = TEAM_ENEMY_0;
	abilities.pushBack(AbilityAttack::create(map, this));
	abilities.pushBack(AbilityMoveTo::create(map, this));
	//abilities.pushBack(AbilityAttack::create(this));
	animations = AnimationSet::create();
	animations->retain();
	direction = 1 + rand() % 8;
	updateAnimation(ANIMATION_IDLE + direction);

	addItem(Item::create());

	return true;
}

void Creature::moveTo(const Vec2& target)
{
	if (movementTarget == target)
		return;
	movementTarget = target;
	shouldUpdatePath = true;
	setupMovement(target);
	updatePathIfCollided();
}

void Creature::moveProcessNextPoint()
{
	if (movingQueue->isEmpty())
	{
		//Set appropriate animation
		stopMoving();
		updateAnimation(ANIMATION_IDLE + direction);
		return;
	}

	setupMovement(movingQueue->back());
	movingQueue->next();
}

void Creature::moveBy(const Vec2& delta)
{
	this->moveTo(getPosition() + delta);
}

void Creature::act(float timeCoefficient)
{
	//this->setRotation(this->getRotation() + timeCoefficient);

	moveStep(timeCoefficient);
}

void Creature::actTenth()
{
	Actor::actTenth();
	updatePathIfCollided();
}

void Creature::moveStep(float timeCoefficient)
{
	if (moveLength > 0)
	{
		setPosition(getPosition() + moveVector * timeCoefficient);
		moveLength -= currentSpeed;
	}
	else
	{
		moveProcessNextPoint();
	}
}

float Creature::getSpeed()
{
	return speed;
}

bool Creature::checkMoveCollision()
{
	Vec2 nextPosition = coordToTile(getPosition() + moveVector * 6, map->tileSize / 4);
	if (int(nextPosition.x) == int(prevTilePos.x) && int(nextPosition.y) == int(prevTilePos.y))
		return false;
	if (map->collision->isWalkable(nextPosition))
		return false;
	return true;
}

void Creature::updatePathIfCollided()
{
	if (moveLength > 0 && checkMoveCollision() && shouldUpdatePath)
	{
		/*if (movingQueue->isGettingToThePoint == false)
		{
			stopMoving();
			movingQueue->isGettingToThePoint = true; //what?
		}
		else*/
		{
			movingQueue->setDestination(movementTarget);
			movingQueue->findPath();
			moveProcessNextPoint();
			shouldUpdatePath = false;
			/*
			if (checkMoveCollision())
				stopMoving();*/
		}
	}
}

void Creature::stopMoving()
{
	moveLength = 0;
	isMoving = false;
}

void Creature::setupMovement(const Vec2& point)
{
	Vec2 fullMoveVector = point - getPosition();


	//Update direction and angle
	directionAngleRadians = std::atan2f(fullMoveVector.y, fullMoveVector.x);
	if (directionAngleRadians > 0)
	{
		if (directionAngleRadians < 0.35f)
			direction = DIRECTION_E;
		else if (directionAngleRadians < 1.22f)
			direction = DIRECTION_NE;
		else if (directionAngleRadians < 1.92f)
			direction = DIRECTION_N;
		else if (directionAngleRadians < 2.79f)
			direction = DIRECTION_NW;
		else
			direction = DIRECTION_W;


		//Calculate move speed, keep in mind isometric length correctness
		currentSpeed = speed - speed / 2 * sin(directionAngleRadians);
	}
	else
	{
		if (directionAngleRadians > -0.35f)
			direction = DIRECTION_E;
		else if (directionAngleRadians > -1.22f)
			direction = DIRECTION_SE;
		else if (directionAngleRadians > -1.92f)
			direction = DIRECTION_S;
		else if (directionAngleRadians > -2.79f)
			direction = DIRECTION_SW;
		else
			direction = DIRECTION_W;


		//Calculate move speed, keep in mind isometric length correctness
		currentSpeed = speed + speed / 2 * sin(directionAngleRadians);
	}

	//Calculate move step vector
	moveVector = scaleTo(fullMoveVector, currentSpeed);

	moveLength = this->getPosition().getDistance(point);

	//Set appropriate animation
	if (prevDirection != direction || !isMoving)
		updateAnimation(ANIMATION_RUN + direction);


	prevDirection = direction;
	isMoving = true;
}

void Creature::attack(Actor * target)
{
	stopMoving();
	if (getPosition().getDistance(target->getPosition()) < attackRange)
		useAbility(ABILITY_ATTACK);
	else
	{
		moveTo(target->getPosition());
		attackOnMoveDone = true;
	}
}

float Creature::getAttackRangeSq()
{
	return attackRange;
}

float Creature::getAttackRange()
{
	return sqrtf(attackRange);
}

void Creature::updateCollisionMap()
{
	map->collision->setCollision(prevTilePos, radius, true);
	prevTilePos = coordToTile(getPosition(), map->tileSize / 4);
	map->collision->setCollision(prevTilePos, radius, false);
}

void Creature::die()
{
	Actor::die();

	//Drop all items
	for (int i = itemsEquipped.size() - 1; i >= 0; --i)
		dropItem(itemsEquipped.at(i));
	for (int i = itemsInventory.size() - 1; i >= 0; --i)
		dropItem(itemsInventory.at(i));
}

void Creature::updateAnimation(size_t animationNumber)
{
	stopAllActions();
	runAction(animations->animations[animationNumber]);
}