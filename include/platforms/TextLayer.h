#pragma once
#include <string>
#include "g2dMath.h"

namespace glowy3d
{

class TextLayer
{
public:
	TextLayer(const std::string& label = "", 
              vec2 position = vec2(0.f, 0.f), 
              float size = 8.f);
	~TextLayer() {}

	void setText(const std::string& text);
	void addText(const std::string& text);
	std::string getText() const;

	void setPosition(vec2 pos);
	void addPosition(vec2 pos);
	vec2 getPosition() const;

	//width
	//line break
	//letter spacing
	//letter height scale


private:
	vec2 position;
	std::string label;
	uint size;
};

}
