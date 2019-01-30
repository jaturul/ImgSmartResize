#include <algorithm>
#include <locale>
#include <string>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "InputParser.h"


InputParser::InputParser()
{
	m_tagCodes = {{"-s", 's'}, {"-i", 'i'}, {"-o", 'o'}, {"-m", 'm'}, {"-d", 'd'}, };
}


InputParser::~InputParser()
{
}

std::vector<std::string> InputParser::parseInput(int argc, char ** argv)
{

	/////// We are assuming CLI input in format:
	// "-s" tag followed by target size (provided as "target_heightxtarget_width")
	// "-i" tag followed by input file name
	// "-o" tag followed by output file name
	// (optional) "-m" tag followed by energy mask file name
	// (optional) "-d" tag followed by "debugDirectory/base_name.png"

	std::vector<std::string> rawInput = getRawInput(argc, argv);
	std::vector<std::string> parsed_input(8);

	// argument at index 0 is omitted as it's the name of the program which isn't needed
	for(unsigned argumentIndex = 1; argumentIndex < rawInput.size(); argumentIndex += 2)
	{
		std::string currentTag= rawInput[argumentIndex];

		if ( !isAcceptableTag(currentTag) ||
			 (argumentIndex + 1 == rawInput.size())  )
		{
			throw "Wrong input arguments have been provided";
		}

		std::string currentArgument = rawInput[argumentIndex + 1];
		switch (m_tagCodes.at(currentTag))
		{
			case ('s'):
			{
				if (!isValidSize(currentArgument))
				{
					throw "Invalid size provided!";
				}

				parsed_input[Constants::InputIndexes::HEIGHT] = getHeight(currentArgument);
				parsed_input[Constants::InputIndexes::WIDTH] = getWidth(currentArgument);

				break;
			}
			case ('i'):
			{
				if (!isImageName(currentArgument))
				{
					throw "Invalid input name provided!";
				}

				parsed_input[Constants::InputIndexes::INPUT] = currentArgument;

				break;
			}
			case ('o'):
			{
				if (!isImageName(currentArgument))
				{
					throw "Invalid input name provided!";
				}

				parsed_input[Constants::InputIndexes::OUTPUT] = currentArgument;

				break;
			}
			case ('m'):
			{
				if (!isImageName(currentArgument))
				{
					throw "Invalid input name provided!";
				}

				parsed_input[Constants::InputIndexes::MASK] = currentArgument;

				break;
			}
			case ('d'):
			{
				if (!isImageName(currentArgument))
				{
					throw "Invalid input name provided!";
				}
				std::string baseName = getImageName(currentArgument);
				std::string extension = getImageExtension(currentArgument);
				parsed_input[Constants::InputIndexes::DEBUG] = "1";
				parsed_input[Constants::InputIndexes::DEBUG_BASE_NAME] = baseName;
				parsed_input[Constants::InputIndexes::DEBUG_EXTENSION] = extension;

				break;
			}
		}
	}

	if(!isValidInput(parsed_input))
	{
		throw "Wrong input arguments have been provided";
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
	std::string fileName = getFilenameFromPath(path);

	std::string name = getImageName(fileName);
	std::string extension = getImageExtension(fileName);

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

bool InputParser::isAcceptableTag(const std::string& tag)
{
	std::vector<std::string> acceptableTags = Constants::ConstantElements::getAcceptableTags();

	for (const auto& acceptableTag: acceptableTags)
	{
		if (tag == acceptableTag)
		{
			return true;
		}
	}

	return false;
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

bool InputParser::isValidInput(const std::vector<std::string> input)
{
	return ( (!input[Constants::InputIndexes::INPUT].empty()) &&
			 (!input[Constants::InputIndexes::OUTPUT].empty()) &&
			 (!input[Constants::InputIndexes::WIDTH].empty()) &&
			 (!input[Constants::InputIndexes::HEIGHT].empty()) );
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

std::string InputParser::getImageExtension(const std::string& imageName)
{
	int dot_index = static_cast<int>(imageName.find("."));

	return std::string(imageName.begin() + dot_index + 1, imageName.end());
}

std::string InputParser::getImageName(const std::string& imageName)
{
	int dot_index = static_cast<int>(imageName.find("."));

	return std::string(imageName.begin(), imageName.begin() + dot_index);
}
