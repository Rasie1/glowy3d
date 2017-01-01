#pragma once
#include "g2dMath.h"
#include "math/quad.h"
#include "platforms/Tex2D.h"

namespace glowy3d
{

class VertexPosBuffer;
class TexCoordsBuffer;
class VertexInterleavedBuffer;
class UniformMat2;
class Sprite;
class Texture;
class TextureAtlas;
class TextureData;

class Layer
{
public:
	//Call Layer::draw every frame. After adding sprites
	//call Layer::updateBuffer
	Layer(uint maxSprites, uint atlasSize = 1024);
	~Layer();
	
	void draw();
	void updateBuffer();
	
	Sprite* add(Texture* texture);
	Sprite* add(const char *imagePath);
	Texture* addTexture(const char *imagePath);
	Texture* addTexture(TextureData* imageData);
	
	void setShader(unsigned shader_id);
	void setTexture(const Tex2D& tex);

	vec2 getPosition() const;
	void setPosition(const vec2& pos);
	void addPosition(const vec2& offset);

	float getRotation() const;
	void setRotation(const float rotation);
	void addRotation(const float offset);

	vec2 getScale() const;
	void setScale(const vec2& scale);
	void addScale(const vec2& offset);

	float getScaleX() const;
	void setScaleX(const float scale);
	void addScaleX(const float offset);

	float getScaleY() const;
	void setScaleY(const float scale);
	void addScaleY(const float offset);

	vec2 getOrigin() const;
	void setOrigin(const vec2& point);

	float getZOrder() const;
	void setZOrder(const float zOrder);
	void addZOrder(const float offset);

private:
	VertexInterleavedBuffer* vertexBuffer;

	quad *vertices;

	mat2 matrix;
	vec2 position;
	float rotation;
	float zOrder;

	uint spritesNum;
	uint maxSprites;
	
	TextureAtlas* textures;

	Tex2D tex2d;

	void bindIbo();
	void bindBuffer();
	void addRotation(const float offset, 
                     const float cosr, 
                     const float sinr);
};

}
