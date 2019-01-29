#ifndef IMAGE_HELPER_H
#define IMAGE_HELPER_H

#include <string>
#include "ImageProcessing/containers/ImageRGB.h"
#include "ImageProcessing/containers/Pixel.h"

class ImageHelper
{
public:

	static ImageRGB loadImageRGB(const std::string& fileName);

	static void saveImage(const ImageRGB& image, const std::string& outputName);

private:
	// raw data of format RGBA is assumed
	static std::vector<Pixel> convertRawToPixelData(const std::vector<unsigned char>& rawData);

	static std::vector<unsigned char> convertImageToRawData(const ImageRGB& image);
};

#endif
