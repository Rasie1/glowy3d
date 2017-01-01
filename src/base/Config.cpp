#include "base/Config.h"
#include "base/ConfigReader.h"
#include <map>

using namespace std;

namespace glowy3d
{

Config::Config()
{
}

Config::Config(const std::string& fileName)
{
	readFromFile(fileName);
}

Config::~Config()
{
}

const uint Config::Default::antialiasingSamples = 16;
const uint Config::Default::maxFramerate = 60;
const bool Config::Default::fullScreen = false;
const usvec2 Config::Default::screenResolution = usvec2(800, 600);
const Config::Platform Config::Default::platform = Config::Platform::D3D11;

void Config::readFromFile(const std::string& filename = "config.txt")
{
	map<string, long> values;
	values["D3D11"] = 0;
	values["OpenGL3"] = 1;

	ConfigReader reader;
	auto settings = reader.read(filename, "glowy2d::Config", values);

	antialiasingSamples = 
		static_cast<uint>(settings["AntialiasingSamples"]);
	screenResolution = 
		usvec2(static_cast<uint16>(settings["ScreenWidth"]),
			   static_cast<uint16>(settings["ScreenHeight"]));
	maxFramerate = 
		static_cast<uint>(settings["MaxFPS"]);
	fullScreen = 
		static_cast<bool>(settings["FullScreen"]);
	platform = 
		static_cast<Platform>(settings["Platform"]);
}

uint Config::getAntialiasing() const
{
	return antialiasingSamples;
}

uint Config::getMaxFramerate() const
{
	return maxFramerate;
}

bool Config::getVSync() const
{
	return maxFramerate != 0;
}

Config::Platform Config::getPlatform() const
{
	return platform;
}

usvec2 Config::getScreenResolution() const
{
	return screenResolution;
}

bool Config::getFullScreen() const
{
	return fullScreen;
}
	
}
