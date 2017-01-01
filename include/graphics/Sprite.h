#pragma once
#include "g2dMath.h"
#include "math/quad.h"

namespace glowy3d
{

class Texture;
class Sprite
{
public:
	Sprite(quad *vboPointer);
	~Sprite();

	bool isHidden() const;
	void setHidden(bool isHidden);

	vec2 getPosition() const;
	void setPosition(const vec2& pos);
	void addPosition(const vec2& offset);

	vec2 getScale() const;
	void setScale(const vec2& scale);
	void addScale(const vec2& offset);

	vec2 getOrigin() const;
	void setOrigin(const vec2& pos);
	void addOrigin(const vec2& offset);

	float getScaleX() const;
	void setScaleX(const float scale);
	void addScaleX(const float offset);

	float getScaleY() const;
	void setScaleY(const float scale);
	void addScaleY(const float offset);

	float getRotation() const;
	void setRotation(const float rotation);
	void addRotation(const float offset);

	float getZOrder() const;
	void setZOrder(const float zorder);
	void addZOrder(const float offset);

	Texture* getTexture() const;
	void setTexture(Texture* texture);

private:
	vec2 position, 
		 scale,
		 origin;
	float rotation;
	bool is_hidden = false;

	quad* coords;
	Texture* texture;

	bool has_changed = true;

	void pointToVbo(float *vbo);
};

}
