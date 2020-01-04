#include "Parser.h"
using namespace std;

Parser::Parser(std::string path)
{
	map.open(path);
	if (!map)
		LOG_warning("path not exist");
}

void Parser::AddParseFunc(const std::string& type, const std::function<ObjectComponent * (std::stringstream&)>& func)
{
	parseFunc.insert({ type, func });
}

void Parser::RemoveParseFunc(const std::string& name)
{
	if (!parseFunc.erase(name))
		LOG_warning(name + " not found");
}

ObjectComponent* Parser::Parse()
{
	// if eof
	if (!getline(map, line))
	{
		return nullptr;
	}
	// else call parser function based on the keyword
	else
	{
		stringstream ss(line);
		string type;
		ss >> type;
		return parseFunc[type](ss);
	}
}


