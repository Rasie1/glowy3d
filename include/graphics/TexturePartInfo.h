#pragma once
#include <string>
#include "g2dMath.h"

//TODO
//-add colors, hsb, shaders, rotation

namespace glowy3d
{

class TexturePartInfo
{
public:
	//This class represents an info about part of TextureInfo
	//such as texture image path, shader, position, color, etc
	TexturePartInfo(const std::string& path, 
					const rect& rectangle = rect(vec2(0.f, 0.f), vec2(1.f, 1.f)));
	~TexturePartInfo();

	const std::string& getPath() const;
	void setPath(const std::string& newPath);
	
	const rect& getRect() const;
	void setRect(const rect& newRect);

private:
	rect rectangle;
	std::string path;
};

}
