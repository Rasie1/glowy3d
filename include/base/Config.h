#pragma once
#include <string>
#include <boost/optional.hpp>
#include "g2dMath.h"

namespace glowy3d
{

class Config
{
public:
	Config(const std::string& filename = "config.txt");

	class Defaults
	{
	public:
		static const usvec2   screenResolution;
		static const uint	  antialiasingSamples;
		static const bool	  fullScreen;
		static const uint	  maxFramerate;
	};

	uint	 getAntialiasing() const;
	uint	 getMaxFramerate() const;
	bool	 getVSync() const;
	usvec2	 getScreenResolution() const;
	bool	 getFullScreen() const;
    std::string getVertexShaderPath() const;
    std::string getFragmentShaderPath() const;

private:
	uint	 antialiasingSamples; 
	uint	 maxFramerate;		 
	usvec2	 screenResolution;	 
	bool	 fullScreen;			 
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

}
