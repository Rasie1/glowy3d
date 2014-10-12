/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2014 Kvachev 'Rasie1' V. D.

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
#include "stdafx.h"
#include "FileOperation.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <dirent.h>
#endif

using namespace std;


std::vector<std::string> FileOperation::listFilesInDirectory(std::string directory)
{
	std::vector<std::string> ret;
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directory.c_str())) != NULL) 
	{
		while ((ent = readdir(dir)) != NULL) 
			ret.push_back(ent->d_name);

		closedir(dir);
	}
	else 
	{
		perror("");
		std:: cout << "dirent error" << endl;
	}
#endif
	
	return ret;
}