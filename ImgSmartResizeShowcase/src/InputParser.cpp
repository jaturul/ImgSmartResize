#include <algorithm>
#include <locale>
#include <string>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "InputParser.h"


InputParser::InputParser()
{
}


InputParser::~InputParser()
{
}

std::vector<std::string> InputParser::parseInput(int argc, char ** argv)
{
	/////// We are assuming CLI input in format:
	// (1) target size (provided as "target_heightxtarget_width")
	// (2) input file name
	// (3) output file name
	// (4) (optional) energy mask file name

	std::vector<std::string> rawInput = getRawInput(argc, argv);
	std::vector<std::string> parsed_input;

	// argument at index 0 is omitted as it's the name of the program which isn't needed
	for (int argumentIndex = 1; argumentIndex < int(rawInput.size()); ++argumentIndex)
	{
		std::string currentArgument = rawInput[argumentIndex];
		switch (argumentIndex)
		{
			case (1):
			{
				if (!isValidSize(currentArgument))
				{
					throw "Invalid size provided!";
				}

				parsed_input.push_back(getHeight(currentArgument));
				parsed_input.push_back(getWidth(currentArgument));

				break;
			}
			case (2):
			case (3):
			case (4):
			{
				if (!isImageName(currentArgument))
				{
					throw "Invalid size provided!";
				}

				parsed_input.push_back(currentArgument);

				break;
			}
			default:
			{
				throw "Wrong number of arguments provided!";
			}
		}
	}

	return parsed_input;
}

std::vector<std::string> InputParser::getRawInput(int argc, char ** argv)
{
	std::vector<std::string> raw_input;

	for (int argument_index = 0; argument_index < argc; ++argument_index)
	{
		std::string current_argument = std::string(argv[argument_index]);
		current_argument.erase(std::remove(current_argument.begin(), current_argument.end(), '\r'), current_argument.end());
		current_argument.erase(std::remove(current_argument.begin(), current_argument.end(), '\n'), current_argument.end());
 		raw_input.push_back(current_argument);
	}

	return raw_input;
}

std::string InputParser::getFilenameFromPath(const std::string & path)
{
	std::string local_path = path;
	int last_slash_index = static_cast<int>(path.find_last_of("\\"));
	if (last_slash_index == -1)
	{
		last_slash_index = static_cast<int>(path.find_last_of("/"));
	}
	std::string result = std::string(local_path.begin() + (last_slash_index + 1), local_path.end());
	return result;
}

bool InputParser::isImageName(const std::string & path)
{
	std::string file_name = getFilenameFromPath(path);
	int dot_index = static_cast<int>(file_name.find("."));

	std::string name(file_name.begin(), file_name.begin() + dot_index);
	std::string extension(file_name.begin() + dot_index + 1, file_name.end());

	if (!isAlphanumerical(name))
	{
		return false;
	}

	if (!isAcceptableImageExtension(extension))
	{
		return false;
	}

	return true;
}

bool InputParser::isAlphanumerical(const std::string & name)
{
	for (const auto& character : name)
	{
		if (!isalnum(character))
		{
			return false;
		}
	}

	return true;
}

bool InputParser::isAcceptableImageExtension(const std::string & extension)
{
	std::string local_extension = extension;
	std::transform(local_extension.begin(), local_extension.end(), local_extension.begin(), ::tolower);

	std::vector<std::string> acceptable_image_extensions = Constants::ConstantElements::getAcceptableImageExtensions();
	for (const auto& acceptable_extension: acceptable_image_extensions)
	{
		if (local_extension == acceptable_extension)
		{
			return true;
		}
	}

	return false;
}

bool InputParser::isNumber(const std::string & number)
{
	for (const auto& digit : number)
	{
		if (!isdigit(digit))
		{
			return false;
		}
	}

	return (true && number.at(0) != '0');
}


bool InputParser::isValidSize(const std::string & sizeStr)
{
	int x_index = static_cast<int>(sizeStr.find_first_of("x"));
	if (x_index == -1)
	{
		throw "Invalid size provided!";
	}
	std::string height = getHeight(sizeStr);
	std::string width = getWidth(sizeStr);

	return (isNumber(width) && isNumber(height));
}

std::string InputParser::getHeight(const std::string & sizeStr)
{
	int x_index = static_cast<int>(sizeStr.find_first_of("x"));
	if (x_index == -1)
	{
		throw "Invalid size provided!";
	}
	return sizeStr.substr(0, x_index);
}

std::string InputParser::getWidth(const std::string & sizeStr)
{
	int x_index = static_cast<int>(sizeStr.find_first_of("x"));
	if (x_index == -1)
	{
		throw "Invalid size provided!";
	}

	return sizeStr.substr(x_index + 1, sizeStr.size() - x_index);
}
