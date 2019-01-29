#include "ImageProcessing/smartResize/ImageCalculator.h"

int ImageCalculator::convolution(ImageGray kernel, ImageGray image)
{
	if ( (kernel.width() != image.width()) ||
		 (kernel.height() != image.height()) )
	{
		throw "Mismatched kernel and image dimensions!";
	}

	flipHorizontally(kernel);
	flipVertically(kernel);

	int result = 0;

	for(unsigned i = 0; i < kernel.height(); ++i)
	{
		for (unsigned j = 0; j < kernel.width(); ++j)
		{
			result += kernel(i,j) * image(i,j);
		}
	}

	return result;
}

Pixel ImageCalculator::convolution(ImageGray kernel, ImageRGB image)
{
	if ( (kernel.width() != image.width()) ||
		 (kernel.height() != image.height()) )
	{
		throw "Mismatched kernel and image dimensions!";
	}

	flipHorizontally(kernel);
	flipVertically(kernel);

	Pixel result{0, 0, 0, 0};

	for(unsigned i = 0; i < kernel.height(); ++i)
	{
		for (unsigned j = 0; j < kernel.width(); ++j)
		{
			result.Red += kernel(i,j) * image(i,j).Red;
			result.Green += kernel(i,j) * image(i,j).Green;
			result.Blue += kernel(i,j) * image(i,j).Blue;
			result.Alpha += kernel(i,j) * image(i,j).Alpha;
		}
	}

	return result;
}

void ImageCalculator::flipHorizontally(ImageGray& image)
{
	unsigned lastRowIndex = image.height() - 1;
	for (unsigned i = 0; i < image.height() / 2; ++i)
	{
		for (unsigned j = 0; j < image.width(); ++j)
		{
			swap(image(i,j), image(lastRowIndex - i, j));
		}
	}
}

void ImageCalculator::flipHorizontally(ImageRGB& image)
{
	unsigned lastRowIndex = image.height() - 1;
	for (unsigned i = 0; i < image.height() / 2; ++i)
	{
		for (unsigned j = 0; j < image.width(); ++j)
		{
			swap(image(i,j), image(lastRowIndex - i, j));
		}
	}
}

void ImageCalculator::flipVertically(ImageGray& image)
{
	unsigned lastColIndex = image.width() - 1;
	for (unsigned i = 0; i < image.height(); ++i)
	{
		for (unsigned j = 0; j < image.width() / 2; ++j)
		{
			swap(image(i,j), image(i, lastColIndex - j));
		}
	}
}

void ImageCalculator::flipVertically(ImageRGB& image)
{
	int lastColIndex = image.width() - 1;
	for (unsigned i = 0; i < image.height(); ++i)
	{
		for (unsigned j = 0; j < image.width() / 2; ++j)
		{
			swap(image(i,j), image(i, lastColIndex - j));
		}
	}
}

void ImageCalculator::swap(Pixel& pixel1, Pixel& pixel2)
{
	Pixel buffer = pixel1;
	pixel1 = pixel2;
	pixel2 = buffer;
}

void ImageCalculator::swap(int& int1, int& int2)
{
	int buffer = int1;
	int1 = int2;
	int2 = buffer;
}
