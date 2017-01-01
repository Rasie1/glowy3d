#include "base/ConfigReader.h"
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

template<typename T, typename Char, typename Traits>
inline std::basic_istream<Char, Traits>& skip(std::basic_istream<Char, Traits>& stream) {
	T unused;
	return stream >> unused;
}

namespace glowy3d
{

std::map<std::string, long> ConfigReader::read(
	const std::string& fileName,
	const std::string& headerName,
	const std::map<string, long>& values = map<string, long>())
{
	ifstream f(fileName);
	auto header = "[" + headerName + "]";
	string curr, name, value;
	long evaluated;
	std::map<std::string, long> ret;

	//Find header
	while (!f.eof())
	{
		getline(f, curr);
		if (curr == header)
			break;
	}

	//Read variables
	while (!f.eof())
	{
		getline(f, curr);
		if (curr[0] == '[')
			break;
		if ((curr[0] < 'a' || curr[0] > 'z') == 
			(curr[0] < 'A' || curr[0] > 'Z'))
			continue;

		stringstream stream(curr);
		stream >> name >> skip<char> >> value;

		if (value[0] >= '0' && value[0] <= '9')
		{
			evaluated = atol(value.c_str()); // there was stol, but gcc was missing it
		}
		else
		{
			if (values.find(value) == values.end())
				evaluated = 0;
			evaluated = values.at(value);
		}
		ret[name] = evaluated;
	}

	return ret;
}

}
