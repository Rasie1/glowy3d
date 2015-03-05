#include "CollisionData.h"
#include <algorithm>
#include <iostream>
#include "Graphics/LineLayer.h"
#include "Engine.h"
#include "MapInfo.h"
#include "Tile.h"
#include "Body.h"
#include "RigidLine.h"
#include "GlobalData.h"

using namespace std;
using namespace glm;
namespace game
{

CollisionData::CollisionData(const MapInfo& map) :
    gravity(vec2(0, 44.f))
{

    staticCollision.resize(map.tiles.size() + 2);
    staticCollision[0].resize(map.tiles[0].size() + 2, false);
    staticCollision[map.tiles.size() + 1].resize(map.tiles[0].size() + 2, false);

    for (uint i = 0; i < map.tiles.size(); ++i)
    {
        staticCollision[i+1].push_back(false);
        for (uint j = 0; j < map.tiles[i].size(); ++j)
            staticCollision[i+1].push_back(map.tiles[i][j]->isSolid());
        staticCollision[i+1].push_back(false);
    }
}

CollisionData::~CollisionData()
{
}

void CollisionData::addBody(Body * body)
{
    dynamicCollision.push_back(body);
}

void CollisionData::removeBody(Body * body)
{
    dynamicCollision.erase(remove(begin(dynamicCollision),
                           end(dynamicCollision),
                           body));
}

void CollisionData::check(Body * body, bool& returnCollided, vec2& returnCollisionPos)
{
    auto pos = body->getPosition();

    returnCollided =  staticCollision[pos.y][pos.x];
}

usvec2 CollisionData::findStart()
{
    for (uint8 i = 1; i < staticCollision.size(); ++i)
    for (uint8 j = 0; j < staticCollision[i].size(); ++j)
        if (staticCollision[i][j])
            return usvec2(j, i);
}

usvec2 nextClockwise(usvec2 current, uint8 clockwiseCounter)
{
    switch (clockwiseCounter)
    {
        case 0:
            return usvec2(current.x - 1, current.y);
        case 1:
            return usvec2(current.x - 1, current.y + 1);
        case 2:
            return usvec2(current.x, current.y + 1);
        case 3:
            return usvec2(current.x + 1, current.y + 1);
        case 4:
            return usvec2(current.x + 1, current.y);
        case 5:
            return usvec2(current.x + 1, current.y - 1);
        case 6:
            return usvec2(current.x, current.y - 1);
        case 7:
            return usvec2(current.x - 1, current.y - 1);
    }
}

void checkDiagonalAndAddIfNeeded(usvec2 prev, usvec2 current, vector<usvec2>& points)
{
    if (prev + usvec2(1, 1) == current)
        points.push_back(prev + usvec2(1, 0));
    if (prev + usvec2(-1, 1) == current)
        points.push_back(prev + usvec2(0, 1));
    if (prev + usvec2(1, -1) == current)
        points.push_back(prev + usvec2(0, -1));
    if (prev + usvec2(-1, -1) == current)
        points.push_back(prev + usvec2(-1, 0));
}

void CollisionData::traceContours(usvec2 start)
{
    for (auto start : tracingPoints)
    {
        vector<usvec2> boundaryPoints;
        boundaryPoints.push_back(start);

        auto currentBoundaryPoint = start;

        uint8 clockwiseCounter = 0;
        auto currentPoint = nextClockwise(currentBoundaryPoint, clockwiseCounter);
        auto backtrackPoint = currentPoint;

        while (currentPoint != start)
        {
            if (staticCollision[currentPoint.y][currentPoint.x])
            {
                checkDiagonalAndAddIfNeeded(currentBoundaryPoint, currentPoint, boundaryPoints);
                boundaryPoints.push_back(currentPoint);
                currentBoundaryPoint = currentPoint;
                currentPoint = backtrackPoint;
                while (currentPoint != nextClockwise(currentBoundaryPoint, clockwiseCounter))
                    clockwiseCounter = (clockwiseCounter + 1) % 8;
            }
            else
            {
                clockwiseCounter = (clockwiseCounter + 1) % 8;
                backtrackPoint   = currentPoint;
                currentPoint     = nextClockwise(currentBoundaryPoint, clockwiseCounter);
            }
        }


        //remove redundant points
        auto prev1 = begin(boundaryPoints);
        auto prev2 = next(begin(boundaryPoints));
        for (uint i = 2; i < boundaryPoints.size();)
        {
            if ((prev1->x == prev2->x && 
                 prev2->x == boundaryPoints[i].x ||
                 prev1->y == prev2->y && 
                 prev2->y == boundaryPoints[i].y) &&
                 boundaryPoints[i] != *prev1)
            {
                boundaryPoints.erase(prev2);
            }
            else
            { 
                ++i;
                prev1 = prev2;
            }
            prev2 = begin(boundaryPoints) + i - 1;
        }

        for (auto first = begin(boundaryPoints), second = prev(end(boundaryPoints));
             first != end(boundaryPoints);)
        {
            auto gap = vec2(0.5, 0.5);
            dynamicCollision.push_back(new RigidLine(vec2(second->x, second->y) - gap,
                                                     vec2(first->x,   first->y) - gap));
            second = first;
            ++first;
        }
    }
}

bool CollisionData::check(usvec2 pos)
{
    return staticCollision[pos.y][pos.x];
}

void CollisionData::collision(Body * body)
{
    for (auto &x : dynamicCollision)
        x->collision(body);
}

vec2 CollisionData::getGravity() const
{
    return gravity;
}

void CollisionData::setGravity(vec2 gravity)
{
    this->gravity = gravity;
}

void CollisionData::addTracingPoint(usvec2 pos)
{
    tracingPoints.push_back(pos + usvec2(1,1));
}

std::vector<glm::usvec2> CollisionData::tracingPoints;

}