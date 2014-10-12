#include "TilesetGenerator.h"

TilesetGenerator * TilesetGenerator::create()
{
	TilesetGenerator * ret = new TilesetGenerator();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TilesetGenerator::init()
{
	return true;
}

Tileset * TilesetGenerator::getTileset()
{
	auto tiles = Tileset::create();
	TextureGenerator * gen = TextureGenerator::create("Textures\\Terrain\\Ground\\grass");
	//gen->retain();
	auto ground = gen->getTexture();
	//ground->retain();
	tiles->add(ground, TILE_GROUND);
	tiles->add(ground, TILE_WALL_SOUTH);
	tiles->add(ground, TILE_WALL_WEST);
	tiles->add(ground, TILE_WALL_CORNER_DOWN);
	TextureGenerator * gen2 = TextureGenerator::create("Textures\\Terrain\\Wall\\bricks", Size(256, 512));
	//gen2->retain();
	auto wall = gen2->getTexture();
	auto wallFlipped = wall->getFlipped(TRANSFORM_FLIP_H);
	//wall->retain();
	wall->add(ground);
	wallFlipped->add(ground);
	//wall->add(TexturePartInfo::create("terrain/wall_0_0.png", Vec2(0, 0), Color4B(0, 0, 0, 0), Size(256, 512)));
	//gen = TextureGenerator::create("ground");
	//tiles->add(gen->getTexture(), TILE_GROUND);
	tiles->add(TextureInfo::create(TexturePartInfo::create("terrain/empty_pixel.png")), TILE_NONE);
	tiles->add(wall, TILE_WALL_EAST);
	tiles->add(wall, TILE_WALL_CORNER_RIGHT);

	/*wall = TextureInfo::create();
	wall->add(TexturePartInfo::create("terrain/grass_0_0.png"));
	wall->add(TexturePartInfo::create("terrain/wall_0_0.png", Vec2(0, 0), Color4B(0, 0, 0, 0), Size(256, 512), 1, TRANSFORM_FLIP_H));*/
	tiles->add(wallFlipped, TILE_WALL_NORTH);
	tiles->add(wallFlipped, TILE_WALL_CORNER_LEFT);

	auto wallDoubled = wall->getFlipped(0);
	wallDoubled->add(wallFlipped);

	tiles->add(wallDoubled, TILE_WALL_CORNER_UP);
	/*
	wall = TextureInfo::create();
	wall->add(TexturePartInfo::create("terrain/wall_1_0.png", Vec2(0, 0), Color4B(0, 0, 0, 0), Size(256, 512), 1, TRANSFORM_FLIP_H);
	tiles->add(wall, TILE_WALL_SOUTH);
	tiles->add(wall, TILE_WALL_WEST);
	*/

	//gen->release();
	//gen2->release();
	return tiles;
}