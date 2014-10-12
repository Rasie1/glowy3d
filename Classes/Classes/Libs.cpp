#include "Libs.h"

USING_NS_CC;

Vec2 coordToTile(const Vec2& point, int tileSize)
{
	return Vec2(point.y / tileSize * 2 + point.x / tileSize, -point.y / tileSize * 2 + point.x / tileSize);
}

Vec2 tileToCoord(const Vec2& point, int tileSize)
{
	return Vec2((point.x + point.y) * tileSize / 2, (point.x - point.y) * tileSize / 4);
}

Vec2 scaleTo(const Vec2& vec, float length)
{
	float len = sqrtf(vec.x * vec.x + vec.y * vec.y);
	return vec / len * length;
}

Texture2D * assembleTexture(TextureInfo * info)
{
	int maxx = 0, maxy = 0, n = (int)(info->parts.size());
	for (int i = 0; i < n; ++i)
	{
		if (info->parts[i]->getSize().width > maxx)
			maxx = info->parts[i]->getSize().width;
		if (info->parts[i]->getSize().height > maxy)
			maxy = info->parts[i]->getSize().height;
		//добавить учет позиции
	}

	auto rt = RenderTexture::create(maxx, maxy);
	rt->retain();
	rt->begin();
	rt->setAutoDraw(false);

	for (int i = 0; i < n; ++i)
	{
		auto spr = Sprite::create(info->parts[i]->getFilePath());
		spr->retain();
		spr->setAnchorPoint(Vec2(0.0f, 0.0f));
		spr->setPosition(info->parts[i]->getPosition() + Vec2(0, maxy - info->parts[i]->getSize().height));
		//spr->setPosition(Vec2(spr->getContentSize().width / 2, (spr->getContentSize().height < 300) ? 0 : -256));
		spr->getTexture()->setAliasTexParameters();
		if (!(info->parts[i]->getTransform() == TRANSFORM_FLIP_V))
			spr->setFlippedY(true);
		if (info->parts[i]->getTransform() == TRANSFORM_FLIP_H)
			spr->setFlippedX(true);
		//spr->setGLProgram(GLProgram::createWithFilenames("Shaders/colorize_saturation.vsh", "Shaders/colorize_saturation.fsh"));
		std::string vertexShader = ccPositionTextureColor_noMVP_vert;
		std::string fragmentShader = FileUtils::getInstance()->getStringFromFile(
			FileUtils::getInstance()->fullPathForFilename("Shaders/colorize_saturation.fsh"));

		spr->setGLProgram(GLProgram::createWithByteArrays(vertexShader.c_str(), fragmentShader.c_str()));
		//initWithByteArrays(ccPositionTextureA8Color_vert, ccPositionTextureA8Color_frag);
		spr->getGLProgramState()->setUniformVec4("u_rgbs", Vec4(info->parts[i]->getColor().r, info->parts[i]->getColor().g, info->parts[i]->getColor().b, 12.0));
		//spr->getGLProgramState()->setUniformVec4("u_rgbs", Vec4(1.0f, 0.0f, 0.0f, 12.0f));

		TextureAssembler::getInstance()->addForDeletion(spr);
		spr->visit();
	}
	rt->end();

	TextureAssembler::getInstance()->addForDeletion(rt);

	auto tex = rt->getSprite()->getTexture();

	/*
	auto rtSprite = rt->getSprite();
	rtSprite->setFlippedY(false);
	auto tex = rtSprite->getTexture();*/

	/*
	std::string str = "temp";
	str += (char)(rand() % 50 + 48);
	str += (char)(rand() % 50 + 48);
	str += (char)(rand() % 50 + 48);
	str += (char)(rand() % 50 + 48);
	str += ".png";*/
	//rt->saveToFile("trt.png", Image::Format::PNG);
	//rt->release();

	return tex;
}

void TextureAssembler::clean()
{
	while (toDelete.size())
	{
		toDelete.back()->release();
		toDelete.popBack();
	}
}

void TextureAssembler::addForDeletion(Node * forDeletion)
{
	toDelete.pushBack(forDeletion);
}

Vec2 difference(Vec2 first, Vec2 second)
{
	return Vec2(second.x - first.x, second.y - first.y);
}

TextureAssembler * TextureAssembler::instance = NULL;
TextureAssembler * TextureAssembler::getInstance()
{
	if (!instance)
		instance = new TextureAssembler();
	return instance;
}

//Vec2i

int Vec2i::getDistance(const Vec2i& point) const
{
	int xx = point.x - x;
	int yy = point.y - y;
	return int(10.0f * sqrtf(float(xx * xx + yy * yy)));
}

bool Vec2i::compare(Vec2i to) const
{
	return x == to.x && y == to.y;
}

Vec2i::operator Vec2() const
{
	return Vec2(x, y);
}

bool Vec2i::operator<(const Vec2i& v) const
{
	if (x == v.x)
		return y < v.y;
	return x < v.x;
}

Vec2iv::operator Vec2i() const
{
	return vec;
}

bool Vec2iv::operator<(const Vec2iv& v) const
{
	return val > v.val;
}

bool Vec2iv::less(const Vec2iv& a, const Vec2iv& b)
{
	return a.val > b.val;
}

bool Vec2iv::compare(const Vec2i& to) const
{
	return vec.compare(to);
}

bool rayTrace(const Vec2& from, const Vec2& target, MapInfo * map)
{
	/*Vec2 _target = -coordToTile(target, map->tileSize) * 4;
	Vec2 _from = -coordToTile(from, map->tileSize) * 4;
	Vec2 fr = Vec2i(_from.x, _from.y - 4);
	Vec2 to = Vec2(_target.x, _target.y - 4);*/

	Vec2 point = from;
	Vec2 step = (target - from).getNormalized() / 20;

	while (point.getDistanceSq(target) > 1)
	{
		if (!(map->collision->isWalkable(point)))
		{
			return true;
		}
		point += step;
	}

	return false;
}