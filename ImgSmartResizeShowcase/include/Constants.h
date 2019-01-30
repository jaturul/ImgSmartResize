#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

namespace Constants
{
	enum InputIndexes { WIDTH = 0, HEIGHT = 1, INPUT = 2, OUTPUT = 3, MASK = 4, DEBUG = 5, DEBUG_BASE_NAME = 6, DEBUG_EXTENSION = 7 };

	class ConstantElements
	{
	public:
		static std::vector<std::string> getAcceptableImageExtensions();
		static std::vector<std::string> getAcceptableTags();
	};
}

#endif
