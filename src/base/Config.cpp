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

    auto pScreenResolutionW = config->get_qualified_as<unsigned short>("Renderer.ScreenWidth");
    auto pScreenResolutionH = config->get_qualified_as<unsigned short>("Renderer.ScreenHeight");
    auto pAntialiasingSamples = config->get_qualified_as<uint>("Renderer.AntialiasingSamples");
    auto pFullScreen = config->get_qualified_as<bool>("Renderer.FullScreen");
    auto pMaxFramerate = config->get_qualified_as<uint>("Renderer.MaxFPS");
    auto pVertexShaderPath = config->get_qualified_as<string>("Renderer.VertexShader");
    auto pFragmentShaderPath = config->get_qualified_as<string>("Renderer.FragmentShader");

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
    if (pVertexShaderPath)
    {
        this->vertexShaderPath = *pVertexShaderPath;
    }
    else
    {
        throw std::runtime_error("No vertex shader specified");
    }
    if (pFragmentShaderPath)
    {
        this->fragmentShaderPath = *pFragmentShaderPath;
    }
    else
    {
        throw std::runtime_error("No fragment shader specified");
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

string Config::getVertexShaderPath() const
{
    return vertexShaderPath;
}

string Config::getFragmentShaderPath() const
{
    return fragmentShaderPath;
}
	
}
