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
#include "Base/ConfigReader.h"
#include <fstream>
#include <sstream>

template<typename T, typename Char, typename Traits>
inline std::basic_istream<Char, Traits>& skip(std::basic_istream<Char, Traits>& stream) {
	T unused;
	return stream >> unused;
}

namespace glowy2d
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