#include "pch.h"

#include "StringUtils.h"

std::vector<std::string> Split(const std::string& str, const char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, delimiter)) tokens.push_back(token);

	return tokens;
}

std::string ThreadIdToString(const std::thread::id& id)
{
	std::ostringstream oss;
	oss << id;
	return oss.str();
}
