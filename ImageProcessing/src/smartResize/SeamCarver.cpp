#include <algorithm>
#include <iostream>

#include "ImageProcessing/smartResize/SeamCarver.h"
#include "ImageProcessing/smartResize/EnergyCalculator.h"
#include "ImageProcessing/containers/Seam.h"

void SeamCarver::resizeImage(ImageRGB& image, const Size& targetSize)
{
	ImageGray energyMap = EnergyCalculator::calculateEnergy(image);
	removeSeams(image, energyMap, targetSize);
}

void SeamCarver::resizeImage(ImageRGB& image, ImageRGB& mask, const Size& targetSize)
{
	ImageGray energyMap = EnergyCalculator::calculateEnergy(image, mask);
	removeSeams(image, energyMap, targetSize);
}

void SeamCarver::removeSeams(ImageRGB& image, ImageGray& energyMap, const Size& targetSize)
{
	// for the moment, we assume only sizes smaller than the target size
	unsigned rowsToRemove = image.height() - targetSize.Height;
	unsigned colsToRemove = image.width() - targetSize.Width;

	std::vector<Orientation> removalOrder = getRemovalOrder(rowsToRemove, colsToRemove);
	for(unsigned i = 0; i < removalOrder.size(); ++i)
	{
		Orientation currentOrientation = removalOrder.at(i);
		ImageGray cummulativeEnergyMap = createCummulativeEnergyMap(energyMap, currentOrientation);

		Seam currentSeam = findSeam(cummulativeEnergyMap, currentOrientation);

		image.removeSeam(currentSeam, currentOrientation);
		energyMap.removeSeam(currentSeam, currentOrientation);
	}
}

ImageGray SeamCarver::createCummulativeEnergyMap(const ImageGray& energyMap, Orientation orientation)
{
	ImageGray cummulativeMap(std::vector<int>(energyMap.width() * energyMap.height()), energyMap.width(), energyMap.height());

	if (orientation == Orientation::Vertical)
	{
		for(unsigned i = 0; i < energyMap.width(); ++i)
		{
			cummulativeMap(0,i) = energyMap.at(0,i);
		}

		for(int i = 1; i < int(energyMap.height()); ++i)
		{
			for(int j = 0; j < int(energyMap.width()); ++j)
			{
				int indexLeftNeighbour= std::max(0, j - 1);
				int indexRightNeighbour= std::min(int(cummulativeMap.width()) - 1, j + 1);
				int indexPrevRow = i -1;

				cummulativeMap(i,j) = energyMap.at(i,j) +
						std::min( cummulativeMap(indexPrevRow, indexLeftNeighbour), std::min(cummulativeMap(indexPrevRow, j), cummulativeMap(indexPrevRow, indexRightNeighbour)) );
			}
		}
	}
	else
	{
		for(unsigned i = 0; i < energyMap.height(); ++i)
		{
			cummulativeMap(i,0) = energyMap.at(i,0);
		}

		for(int i = 1; i < int(energyMap.width()); ++i)
		{
			for(int j = 0; j < int(energyMap.height()); ++j)
			{
				int indexTopNeighbour= std::max(0, j - 1);
				int indexBottomNeighbour= std::min(int(cummulativeMap.height()) - 1, j + 1);
				int indexPrevCol = i - 1;

				cummulativeMap(j, i) = energyMap.at(j, i) +
						std::min( cummulativeMap(indexTopNeighbour, indexPrevCol), std::min(cummulativeMap(j, indexPrevCol), cummulativeMap(indexBottomNeighbour, indexPrevCol)) );
			}
		}
	}

	return cummulativeMap;
}

std::vector<Orientation> SeamCarver::getRemovalOrder(int rowsToRemove, int colsToRemove)
{
	const int totalRemovalNumber = rowsToRemove + colsToRemove;
	std::vector<Orientation> removalOrder;
	for(int i = 0; i < totalRemovalNumber; ++i)
	{
		if( (rowsToRemove > 0) && (colsToRemove > 0) )
		{
			if (i % 2 == 0)
			{
				removalOrder.push_back(Orientation::Vertical);
				--colsToRemove;
			}
			else if (i % 2 == 1)
			{
				removalOrder.push_back(Orientation::Horizontal);
				--rowsToRemove;
			}
		}
		else
		{
			if(rowsToRemove == 0)
			{
				removalOrder.push_back(Orientation::Vertical);
			}
			else if (colsToRemove == 0)
			{
				removalOrder.push_back(Orientation::Horizontal);
			}
		}
	}

	return removalOrder;
}

Seam SeamCarver::findSeam(const ImageGray& cummulativeEnergyMap, Orientation orientation)
{
	if (orientation == Orientation::Vertical)
	{
		unsigned lastRow = cummulativeEnergyMap.height() - 1;
		unsigned currentMinEnergyCol = 0;
		int minEnergy = cummulativeEnergyMap.at(lastRow, currentMinEnergyCol);
		for (unsigned col = 1; col < cummulativeEnergyMap.width(); ++col)
		{
			if (cummulativeEnergyMap.at(lastRow, col) < minEnergy)
			{
				currentMinEnergyCol = col;
				minEnergy = cummulativeEnergyMap.at(lastRow, col);
			}
		}
		Coord2D startingPoint(lastRow, currentMinEnergyCol);

		Seam seam(Orientation::Vertical);
		seam.addElement(startingPoint);

		int prevMinEnergyCol = startingPoint.Col();
		for(int row = int(lastRow) - 1; row >= 0; --row)
		{
			int leftCol= std::max(0, prevMinEnergyCol - 1);
			int middleCol = prevMinEnergyCol;
			int rightCol= std::min(int(cummulativeEnergyMap.width()) - 1, prevMinEnergyCol + 1);

			// to start with, we assume the pixel to the top left has minimal energy
			int minEnergy = cummulativeEnergyMap.at(row, leftCol);
			int currentMinEnergyCol = leftCol;

			if (cummulativeEnergyMap.at(row, middleCol) < minEnergy)
			{
				minEnergy = cummulativeEnergyMap.at(row, middleCol);
				currentMinEnergyCol = middleCol;
			}
			else if (cummulativeEnergyMap.at(row, rightCol) < minEnergy)
			{
				minEnergy = cummulativeEnergyMap.at(row, rightCol);
				currentMinEnergyCol = rightCol;
			}

			seam.addElement(Coord2D(row, currentMinEnergyCol));

			prevMinEnergyCol = currentMinEnergyCol;
		}

		return seam;
	}
	else if (orientation == Orientation::Horizontal)
	{
		unsigned lastCol = cummulativeEnergyMap.width() - 1;
		unsigned currentMinEnergyRow = 0;
		int minEnergy = cummulativeEnergyMap.at(currentMinEnergyRow , lastCol);
		for (unsigned row = 1; row < cummulativeEnergyMap.height(); ++row)
		{
			if (cummulativeEnergyMap.at(row, lastCol) < minEnergy)
			{
				currentMinEnergyRow = row;
				minEnergy = cummulativeEnergyMap.at(row, lastCol);
			}
		}
		Coord2D startingPoint(currentMinEnergyRow , lastCol);

		Seam seam(Orientation::Horizontal);
		seam.addElement(startingPoint);

		int prevMinEnergyRow = startingPoint.Row();
		for(int col = int(lastCol) - 1; col >= 0; --col)
		{
			int topRow = std::max(0, prevMinEnergyRow - 1);
			int middleRow = prevMinEnergyRow;
			int bottomRow= std::min(int(cummulativeEnergyMap.height()) - 1, prevMinEnergyRow + 1);

			// to start with, we assume the pixel to the top left has minimal energy
			int minEnergy = cummulativeEnergyMap.at(topRow, col);
			currentMinEnergyRow = topRow;

			if (cummulativeEnergyMap.at(middleRow, col) < minEnergy)
			{
				minEnergy = cummulativeEnergyMap.at(middleRow, col);
				currentMinEnergyRow = middleRow;
			}

			if (cummulativeEnergyMap.at(bottomRow, col) < minEnergy)
			{
				minEnergy = cummulativeEnergyMap.at(bottomRow, col);
				currentMinEnergyRow = bottomRow;
			}

			seam.addElement(Coord2D(currentMinEnergyRow, col));

			prevMinEnergyRow = currentMinEnergyRow;
		}

		return seam;
	}
}
