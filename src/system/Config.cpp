/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2015 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "epc.h"
#include "Base/Config.h"
#include "Base/ConfigReader.h"
#include <map>

namespace glowy2d
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
	values["D3D11"] = 1;
	values["OpenGL3"] = 0;

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