//============================================================================
// Name        : TooplooxSeamCarving.cpp
// Author      : Jacek Turula
// Version     :
// Copyright   : This program has been written by Jacek Turula.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "lodepng/include/lodepng.h"

#include "ImageProcessing/containers/ImageRGB.h"
#include "ImageProcessing/containers/ImageGray.h"
#include "ImageProcessing/containers/Orientation.h"
#include "ImageProcessing/smartResize/SeamCarver.h"
#include "ImageProcessing/smartResize/EnergyCalculator.h"

#include "Constants.h"
#include "ImageHelper.h"
#include "InputParser.h"


bool isMaskProvided(const std::vector<std::string>& arguments)
{
	return !(arguments.at(Constants::InputIndexes::MASK).empty());
}

bool isDebugEnabled(const std::vector<std::string>& arguments)
{
	return !(arguments.at(Constants::InputIndexes::DEBUG).empty());
}

void saveSeamImages(const std::vector<ImageRGB>& seamImages, const std::vector<std::string>& arguments)
{
	std::string baseName = arguments[Constants::InputIndexes::DEBUG_BASE_NAME];
	std::string extension = arguments[Constants::InputIndexes::DEBUG_EXTENSION];

	for(unsigned i = 0; i < seamImages.size(); ++i)
	{
		ImageHelper::saveImage(seamImages[i], baseName + std::to_string(i) + extension);
	}
}

int main(int argc, char** argv)
{
	try
	{
		InputParser inputParser;
		std::vector<std::string> arguments = inputParser.parseInput(argc, argv);

		ImageRGB input = ImageHelper::loadImageRGB(arguments[Constants::InputIndexes::INPUT]);
		bool debug = isDebugEnabled(arguments);
		Size targetSize(std::stoi(arguments[Constants::InputIndexes::WIDTH]), std::stoi(arguments[Constants::InputIndexes::HEIGHT]));

		SeamCarver carver;
		if (isMaskProvided(arguments))
		{
			std::string energyMask = arguments[Constants::InputIndexes::MASK];
			ImageRGB mask = ImageHelper::loadImageRGB(energyMask);
			if(debug)
			{
				carver.enableDebugMode();
				std::vector<ImageRGB> seamImages = carver.resizeImage(input, mask, targetSize);
				saveSeamImages(seamImages, arguments);
			}
			else
			{
				carver.resizeImage(input, mask, targetSize);
			}
		}
		else
		{
			if(debug)
			{
				carver.enableDebugMode();
				std::vector<ImageRGB> seamImages = carver.resizeImage(input, targetSize);

				saveSeamImages(seamImages, arguments);
			}
			else
			{
				carver.resizeImage(input, targetSize);
			}
		}

		std::string outputFile = arguments[3];
		ImageHelper::saveImage(input, outputFile);
	}
	catch(char const* e)
	{
		std::cout << e << std::endl;
	}

	return 0;
}
