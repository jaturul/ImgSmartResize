#ifndef IMAGE_RGB_H
#define IMAGE_RGB_H

#include <vector>

#include "ImageProcessing/containers/Pixel.h"
#include "ImageProcessing/containers/Size.h"
#include "ImageProcessing/containers/Orientation.h"
#include "ImageProcessing/containers/Seam.h"

class ImageRGB
{
public:
	ImageRGB();
	ImageRGB(std::vector<Pixel> data, unsigned width, unsigned height);

	unsigned width() const;
	unsigned height() const;

	// indexes from range <0, width/height) are assumed!
	Pixel at(unsigned row, unsigned col) const;
	Pixel& operator()(unsigned row, unsigned col);
	ImageRGB neighbourhood(unsigned row, unsigned col) const;
	void removeSeam(const Seam& seam, Orientation orientation);


	//DEBUG
	void markSeam(const Seam& seam);

private:
	std::vector<unsigned> convertSeamTo1DCoord(const Seam& seam, unsigned imageWidth);
	std::vector<Pixel> m_data;
	Size m_size;
};

#endif
