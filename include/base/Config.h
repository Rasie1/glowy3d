#pragma once
#include <string>
#include "g2dMath.h"

namespace glowy3d
{

class Config
{
public:
	Config();
	Config(const std::string& fileName);
	~Config();

	enum Platform
	{
		OpenGL3,
		D3D11,
	};

	class Default
	{
	public:
		static const usvec2   screenResolution;
		static const Platform platform;
		static const uint	  antialiasingSamples;
		static const bool	  fullScreen;
		static const uint	  maxFramerate;
	};

	void readFromFile(const std::string& filename);

	uint	 getAntialiasing() const;
	uint	 getMaxFramerate() const;
	bool	 getVSync() const;
	Platform getPlatform() const;
	usvec2	 getScreenResolution() const;
	bool	 getFullScreen() const;

private:
	uint	 antialiasingSamples = Default::antialiasingSamples;
	uint	 maxFramerate		 = Default::maxFramerate;
	Platform platform		     = Default::platform;
	usvec2	 screenResolution	 = Default::screenResolution;
	bool	 fullScreen			 = Default::fullScreen;
};

}
