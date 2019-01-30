#include "Constants.h"

std::vector<std::string> Constants::ConstantElements::getAcceptableImageExtensions()
{
	return std::vector<std::string>{"png"};
}

std::vector<std::string> Constants::ConstantElements::getAcceptableTags()
{
	return std::vector<std::string>{"-s", "-i", "-o", "-m", "-d"};
}
