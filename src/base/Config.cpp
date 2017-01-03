#include "base/Config.h"
#include "base/ConfigReader.h"
#include <cpptoml.h>
#include <map>
#include <iostream>

using namespace std;

namespace glowy3d
{

Config::Config(const std::string& filename)
{
    auto config = cpptoml::parse_file(filename);

    auto pScreenResolutionW = config->get_qualified_as<unsigned short>("glowy3d.ScreenWidth");
    auto pScreenResolutionH = config->get_qualified_as<unsigned short>("glowy3d.ScreenHeight");
    auto pAntialiasingSamples = config->get_qualified_as<uint>("glowy3d.AntialiasingSamples");
    auto pFullScreen = config->get_qualified_as<bool>("glowy3d.FullScreen");
    auto pMaxFramerate = config->get_qualified_as<uint>("glowy3d.MaxFPS");

    if (pScreenResolutionH && pScreenResolutionW)
    {
        this->screenResolution = usvec2(*pScreenResolutionW, *pScreenResolutionH);
    }
    else
    {
        this->screenResolution = Defaults::screenResolution;
    }
    if (pAntialiasingSamples)
    {
        this->antialiasingSamples = *pAntialiasingSamples;
    }
    else
    {
        this->antialiasingSamples = Defaults::antialiasingSamples;
    }
    if (pFullScreen)
    {
        this->fullScreen = *pFullScreen;
    }
    else
    {
        this->fullScreen = Defaults::fullScreen;
    }
    if (pMaxFramerate)
    {
        this->maxFramerate = *pMaxFramerate;
    }
    else
    {
        this->maxFramerate = Defaults::maxFramerate;
    }
}


const uint   Config::Defaults::antialiasingSamples = 4;
const uint   Config::Defaults::maxFramerate = 60;
const bool   Config::Defaults::fullScreen = false;
const usvec2 Config::Defaults::screenResolution = usvec2(800, 600);

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

usvec2 Config::getScreenResolution() const
{
	return screenResolution;
}

bool Config::getFullScreen() const
{
	return fullScreen;
}
	
}
