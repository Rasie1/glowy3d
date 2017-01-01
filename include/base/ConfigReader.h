#pragma once
#include <string>
#include <map>

namespace glowy3d
{

class ConfigReader
{
public:
	//Searches in file for specified header and then return map of
	//all the declarations written under header in the format of :
	//PARAM_NAME = VALUE
	//Header name within a file must be enclosed with "[" and "]"
	//@param values - if the value is a string, it will be searched 
	//in this container
	std::map<std::string, long> read(const std::string& fileName,
									 const std::string& headerName,
									 const std::map<std::string, long>& values);
};

}
