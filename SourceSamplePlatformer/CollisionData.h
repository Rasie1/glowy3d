#pragma once
#include <vector>
#include "Math/AdditionGLM.h"

namespace glowy2d
{
class LineLayer;
class Layer;
}

namespace game
{

class MapInfo;
class Body;
class CollisionData
{
public:
    CollisionData(const MapInfo& map);
    ~CollisionData();

    void addBody(Body * body);
    void removeBody(Body * body);

    void collision(Body * body);
    void check(Body * body, bool& returnCollided, glm::vec2& returnCollisionPos);
    bool check(glm::usvec2 pos);

    void traceContours(glm::usvec2 start);

    glm::vec2 getGravity() const;
    void setGravity(glm::vec2 gravity);

    //Add a tracing point for a set of connected solid blocks on map
    //to trace them and make them solid in-game
    static void addTracingPoint(glm::usvec2 pos);

private:
    glm::vec2 gravity;

    std::vector<std::vector<bool>> staticCollision;
    std::vector<Body*> dynamicCollision;
    static std::vector<glm::usvec2> tracingPoints;

    glm::usvec2 findStart();
};

}