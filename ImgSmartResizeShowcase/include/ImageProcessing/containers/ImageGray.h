#ifndef IMAGE_GRAY_H
#define IMAGE_GRAY_H

#include <vector>

#include "ImageProcessing/containers/Size.h"
#include "ImageProcessing/containers/Seam.h"
#include "ImageProcessing/containers/Orientation.h"

class ImageGray
{
public:
	ImageGray();
	ImageGray(std::vector<int> data, unsigned width, unsigned height);

	unsigned width() const;
	unsigned height() const;

	// indexes from range <0, width/height) are assumed!
	int at(unsigned row, unsigned col) const;
	int& operator()(unsigned row, unsigned col);
	ImageGray neighbourhood(unsigned row, unsigned col) const;

	void removeSeam(const Seam& seam, Orientation orientation);

private:
	std::vector<unsigned> convertSeamTo1DCoord(const Seam& seam, unsigned imageWidth);
	std::vector<int> m_data;
	Size m_size;
};

#endif
