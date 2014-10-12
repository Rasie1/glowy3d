#ifndef __LIBS_H__
#define __LIBS_H__

#include "cocos2d.h"
#include "MapInfo.h"/*
#include "Actor.h"
#include "Creature.h"
#include "MapNode.h"
#include "TileInfo.h"*/

#define assembleTexture TextureAssembler::assembleTextureWithInfo

USING_NS_CC;

class TextureInfo;
class World;
class MapInfo;
struct Vec2i;
struct Vec2iv;

enum AbilityNames
{
	ABILITY_ATTACK,
	ABILITY_MOVETO
};

enum MapTypeNames
{
	MAPTYPE_DUNGEON,
	MAPTYPE_DESERT
};

enum CollisionTypes
{
	COLLISION_EMPTY,
	COLLISION_FULL,
	COLLISION_BOTTOM,
	COLLISION_UP,
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_SMALL
};

enum TileTypes
{
	TILE_NONE,
	TILE_GROUND,
	TILE_WALL_NORTH,
	TILE_WALL_EAST,
	TILE_WALL_SOUTH,
	TILE_WALL_WEST,
	TILE_WALL_CORNER_UP,
	TILE_WALL_CORNER_DOWN,
	TILE_WALL_CORNER_LEFT,
	TILE_WALL_CORNER_RIGHT,
	TILE_BARREL
};

enum DirectionNames
{
	DIRECTION_UNDEFINED,
	DIRECTION_N,
	DIRECTION_NE,
	DIRECTION_E,
	DIRECTION_SE,
	DIRECTION_S,
	DIRECTION_SW,
	DIRECTION_W,
	DIRECTION_NW,
	DIRECTION_UPPERLEFT_BOTTOMRIGHT,
	DIRECTION_BOTTOMLEFT_UPPERRIGHT,
	DIRECTION_TOP,
	DIRECTION_RIGHT,
	DIRECTION_BOTTOM,
	DIRECTION_LEFT,
};

enum DamageTypes
{
	DMGTYPE_DIRECT,
	DMGTYPE_PIERCE,
	DMGTYPE_BLUNT,
	DMGTYPE_FIRE,
	DMGTYPE_POISON,
	DMGTYPE_COLD,
	DMGTYPE_LIGHTNING,
	DMGTYPE_ARCANE,
	DMGTYPE_DARK,
	DMGTYPE_LIGHT,
	DMGTYPE_BLEEDING,
	DMGTYPE_ACID,
	DMGTYPE_MAGIC_BURN
};

enum TransformNames
{
	TRANSFORM_NONE,
	TRANSFORM_FLIP_H,
	TRANSFORM_FLIP_V,
	TRANSFORM_ROTATE_180,
	TRANSFORM_ROTATE_CW,
	TRANSFORM_ROTATE_CCW
};

enum GameConstants
{
	kTileTextureSize = 256,
	kChunkSize = 16,
	kDefaultMapSize = 32,
	kDefaultDungeonPowerPoints = 5000,
	kDefaultDungeonRoomCost = 100,
	kZoomSpeed = 1,
};

enum AiStates
{
	AI_STATE_STANDBY,
	AI_STATE_FIGHT,
	AI_STATE_FLEE,
	AI_STATE_HIDDEN
};

enum TeamNumbers
{
	TEAM_NEUTRAL,
	TEAM_PLAYER,
	TEAM_NPC,
	TEAM_ENEMY_0,
	TEAM_ENEMY_1,
	TEAM_ENEMY_2,
	TEAM_ENEMY_3,
};

enum ActorTypes
{
	ACTORTYPE_NONE,
	ACTORTYPE_ITEM,
	ACTORTYPE_PLAYER,
	ACTORTYPE_NPC,
	ACTORTYPE_MONSTER
};

enum MonsterSpecies
{
	MONSTER_SPECIES_UNKNOWN,
	MONSTER_SPECIES_HUMANOID,
	MONSTER_SPECIES_BEAST,
	MONSTER_SPECIES_MAGIC,
	MONSTER_SPECIES_UNDEAD
};

enum GameConstantsLower
{
	kVisibleSpritesRange = 8,
	kActorsSleepRadius = 900000,
	kMaxPathfindingOperations = 512
};

//Returns tile coordinates of point
Vec2 coordToTile(const Vec2& point, int tileSize);

//Vec2 coordToTileCen(Vec2 point, Size tileSize);
//Returns global coordinates of tile
Vec2 tileToCoord(const Vec2& point, int tileSize);

//Scales Vec2 to specified length. (normalize and multiply) Uses sqrtf
Vec2 scaleTo(const Vec2& vec, float length);

//Class to make Texture2D out of TextureInfo
class TextureAssembler
{
public:
	//Returns a Texture2d made out of TextureInfo. Attention: function
	//adds something as a child to (Node * deleter) with tag "_assembleTexture"
	//You have to release it later (not immediately), otherwise there will be
	//leaked sprites and textures.
	static Texture2D * assembleTextureWithInfo(TextureInfo * info);
	//Don't call right after assembling. It's automatically called each 5 seconds.
	//Delay is required.
	void clean();
	//Releases node later
	void addForDeletion(Node * forDeletion);
	static TextureAssembler * getInstance();
private:
	TextureAssembler(){}
	Vector<Node*> toDelete;
	static TextureAssembler * instance;
};//TODO remove singleton

//Returns difference between two vectors (vector from first to second)
Vec2 difference(Vec2 first, Vec2 second);

//Point represented by integers and not floats like Vec2
struct Vec2i
{
	int x, y;

	Vec2i(int xx = 0, int yy = 0) : x(xx), y(yy) {}

	bool compare(Vec2i to) const;
	operator Vec2() const;
	bool operator<(const Vec2i& v) const;
	int getDistance(const Vec2i& point) const;
};

//Point plus integer field. Used in pathfinding
struct Vec2iv
{
	Vec2i vec;
	int val;

	Vec2iv(Vec2i vect, int value) : vec(vect), val(value) {}

	operator Vec2i() const;
	bool operator<(const Vec2iv& v) const;
	static bool less(const Vec2iv& a, const Vec2iv& b);
	bool compare(const Vec2i& to) const;
};

//Integer rectangle
struct Recti
{
	int x, y, w, h;

	Recti(int xx, int yy, int width, int height) : x(xx), y(yy), w(width), h(height) {}

	//bool isInside();
};

//Return true if collides with something
bool rayTrace(const Vec2& from, const Vec2& target, MapInfo * map);

#endif