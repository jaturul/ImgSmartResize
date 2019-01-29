#include <algorithm>
#include <stdexcept>

#include "ImageProcessing/containers/ImageRGB.h"

ImageRGB::ImageRGB() :
	m_data(std::vector<Pixel>()),
	m_size(0,0)
{

}

ImageRGB::ImageRGB(std::vector<Pixel> data, unsigned width, unsigned height) :
	m_data(data),
	m_size(width,height)
{
	if(width * height != data.size())
	{
		throw std::invalid_argument("Provided image data and size are mismatched!");
	}

}

unsigned ImageRGB::width() const
{
	return m_size.Width;
}

unsigned ImageRGB::height() const
{
	return m_size.Height;
}

Pixel ImageRGB::at(unsigned row, unsigned col) const
{
	unsigned index = row * m_size.Width + col;
	return m_data[index];
}

Pixel& ImageRGB::operator()(unsigned row, unsigned col)
{
	unsigned index = row * m_size.Width + col;
	return m_data[index];
}

ImageRGB ImageRGB::neighbourhood(unsigned row, unsigned col) const
{
	// Extracts a 3x3 image neighbourhood
	// Areas outside image coordinates are set to border values
	std::vector<Pixel> neighbourhoodData( 3 * 3, {0,0,0,0});
	ImageRGB neighbourhood(neighbourhoodData, 3, 3);

	for(int i = -1; i < 2; ++i)
	{
		for(int j = -1; j < 2; ++j)
		{
			int currRow = std::max(0, int(row) + i);
			currRow = std::min(currRow, int(height()) - 1);

			int currCol = std::max(0, int(col) + j);
			currCol = std::min(currCol, int(width()) - 1);

			neighbourhood(i + 1, j + 1) = this->at(currRow, currCol);
		}
	}

	return neighbourhood;
}

std::vector<unsigned> ImageRGB::convertSeamTo1DCoord(const Seam& seam, unsigned imageWidth)
{
	std::vector<unsigned> coordinates1D(seam.size());
	for(int i = 0; i < seam.size(); ++i)
	{
		coordinates1D[i] = seam.at(i).Row() * imageWidth + seam.at(i).Col();
	}

	return coordinates1D;
}

void swap(Pixel& pixel1, Pixel& pixel2)
{
	Pixel buffer = pixel1;
	pixel1 = pixel2;
	pixel2 = buffer;
}

void ImageRGB::removeSeam(const Seam& seam, Orientation orientation)
{
	if (orientation == Orientation::Vertical)
	{
		std::vector<unsigned> pointsToRemove = convertSeamTo1DCoord(seam, this->width());
		std::sort(pointsToRemove.rbegin(), pointsToRemove.rend());
		for (unsigned i = 0; i < pointsToRemove.size(); ++i)
		{
			m_data.erase(m_data.begin() + pointsToRemove[i]);
		}

		m_size.Width--;
	}
	else if (orientation == Orientation::Horizontal)
	{
		unsigned lastRow = height() - 1;
		for (unsigned i = 0; i < seam.size(); ++i)
		{
			unsigned currentCol = seam.at(i).Col();
			for(unsigned currentRow = seam.at(i).Row(); currentRow != lastRow; ++currentRow )
			{
				swap((*this)(currentRow, currentCol), (*this)(currentRow + 1, currentCol));
			}
		}

		m_data.erase(m_data.begin() + lastRow * width(), m_data.end());
		m_size.Height--;
	}
}

//DEBUG
void ImageRGB::markSeam(const Seam& seam)
{
	Pixel markedPixel;
	markedPixel.Red = 255;
	markedPixel.Green = 0;
	markedPixel.Blue = 0;
	markedPixel.Alpha = 255;

	for(int i = 0; i < seam.size(); ++i)
	{
		int currCol = seam.at(i).Col();
		int currRow = seam.at(i).Row();

		(*this)(currRow, currCol) = markedPixel;
	}
}
