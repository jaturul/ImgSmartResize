#include <stdexcept>

#include "lodepng/include/lodepng.h"

#include "ImageHelper.h"

namespace
{
	const int RGBA_WIDTH = 4;
}

ImageRGB ImageHelper::loadImageRGB(const std::string& fileName)
{
	std::vector<unsigned char> rawData;
	unsigned width;
	unsigned height;
	unsigned decodeError = lodepng::decode(rawData, width, height, fileName);

	if (decodeError)
	{
		throw lodepng_error_text(decodeError);
	}

	std::vector<Pixel> imageData = convertRawToPixelData(rawData);

	return ImageRGB(imageData, width, height);
}

std::vector<Pixel> ImageHelper::convertRawToPixelData(const std::vector<unsigned char>& rawData)
{
	int imageDataWidth = rawData.size() / RGBA_WIDTH;
	std::vector<Pixel> imageData(imageDataWidth);

	for(int i = 0; i != imageDataWidth; ++i)
	{
		Pixel currentPixel;
		currentPixel.Red = int(rawData[i * RGBA_WIDTH]);
		currentPixel.Green = int(rawData[i * RGBA_WIDTH + 1]);
		currentPixel.Blue = int(rawData[i * RGBA_WIDTH + 2]);
		currentPixel.Alpha = int(rawData[i * RGBA_WIDTH + 3]);

		imageData[i] = currentPixel;
	}

	return imageData;
}

void ImageHelper::saveImage(const ImageRGB& image, const std::string& imageName)
{
	std::vector<unsigned char> rawImageData = convertImageToRawData(image);
	unsigned encodeError = lodepng::encode(imageName, rawImageData, image.width(), image.height());

	if(encodeError)
	{
		throw lodepng_error_text(encodeError);
	}
}

std::vector<unsigned char> ImageHelper::convertImageToRawData(const ImageRGB& image)
{
	int dataSize = image.width() * image.height() * RGBA_WIDTH;
	std::vector<unsigned char> rawData(dataSize);

	for(unsigned i = 0; i < image.height(); ++i)
	{
		for(unsigned j = 0; j < image.width(); ++j)
		{
			int currentIndex = (i * image.width() + j) * RGBA_WIDTH;
			rawData[currentIndex] = (unsigned char)(image.at(i,j).Red);
			rawData[currentIndex + 1] = (unsigned char)(image.at(i,j).Green);
			rawData[currentIndex + 2] = (unsigned char)(image.at(i,j).Blue);
			rawData[currentIndex + 3] = (unsigned char)(image.at(i,j).Alpha);
		}
	}

	return rawData;
}
