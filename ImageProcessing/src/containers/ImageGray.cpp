#include <algorithm>
#include "ImageProcessing/containers/ImageGray.h"

namespace
{
	const int MAX_NEIGHBOURHOOD_INDEX = 1;
	const int MIN_NEIGHBOURHOOD_INDEX = -1;
}

ImageGray::ImageGray():
	m_data(std::vector<int>()),
	m_size(0,0)
{

}

ImageGray::ImageGray(std::vector<int> data, unsigned width, unsigned height):
	m_data(data),
	m_size(width, height)
{

}

unsigned ImageGray::width() const
{
	return m_size.Width;
}

unsigned ImageGray::height() const
{
	return m_size.Height;
}

// indexes from range <0, width/height) are assumed!
int ImageGray::at(unsigned row, unsigned col) const
{
	int currentIndex = row * width() + col;

	return m_data[currentIndex];
}

int& ImageGray::operator()(unsigned row, unsigned col)
{
	int currentIndex = row * width() + col;

	return m_data[currentIndex];
}

ImageGray ImageGray::neighbourhood(unsigned row, unsigned col) const
{
	// Extracts a 3x3 image neighbourhood
	// Areas outside image coordinates are set to border values
	std::vector<int> neighbourhoodData( 3 * 3, 0);
	ImageGray neighbourhood(neighbourhoodData, 3, 3);

	for(int i = MIN_NEIGHBOURHOOD_INDEX; i <= MAX_NEIGHBOURHOOD_INDEX; ++i)
	{
		for(int j = MIN_NEIGHBOURHOOD_INDEX; j <= MAX_NEIGHBOURHOOD_INDEX; ++j)
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

void swap(int& int1, int& int2)
{
	int buffer = int1;
	int1 = int2;
	int2 = buffer;
}

void ImageGray::removeSeam(const Seam& seam, Orientation orientation)
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
		for (int i = 0; i < int(seam.size()); ++i)
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

std::vector<unsigned> ImageGray::convertSeamTo1DCoord(const Seam& seam, unsigned imageWidth)
{
	std::vector<unsigned> coordinates1D(seam.size());
	for(int i = 0; i < seam.size(); ++i)
	{
		coordinates1D[i] = seam.at(i).Row() * imageWidth + seam.at(i).Col();
	}

	return coordinates1D;
}
