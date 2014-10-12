#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include "cocos2d.h"
USING_NS_CC;

class FileOperation 
{
public:
	static void saveFile(void);
	static void readFile(void);
	static std::string getFilePath();
	static std::vector<std::string> listFilesInDirectory(std::string path);
};

#endif
