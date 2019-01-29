#ifndef IMAGE_CALCULATOR_H
#define IMAGE_CALCULATOR_H

#include "ImageProcessing/containers/ImageGray.h"
#include "ImageProcessing/containers/ImageRGB.h"

class ImageCalculator
{
public:
	static int convolution(ImageGray kernel, ImageGray image);
	static Pixel convolution(ImageGray kernel, ImageRGB image);

private:
	static void flipHorizontally(ImageGray& image);
	static void flipHorizontally(ImageRGB& image);

	static void flipVertically(ImageGray& image);
	static void flipVertically(ImageRGB& image);

	static void swap(Pixel& pixel1, Pixel& pixel2);
	static void swap(int& int1, int& int2);
};

#endif
