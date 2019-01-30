#ifndef SEAM_CARVER_H
#define SEAM_CARVER_H

#include <memory>

#include "ImageProcessing/containers/ImageRGB.h"
#include "ImageProcessing/containers/ImageGray.h"
#include "ImageProcessing/containers/Size.h"
#include "ImageProcessing/containers/Seam.h"
#include "ImageProcessing/containers/Orientation.h"
#include "ImageProcessing/smartResize/EnergyCalculator.h"


class SeamCarver
{
public:
	SeamCarver();
	std::vector<ImageRGB> resizeImage(ImageRGB& image, ImageRGB& mask, const Size& targetSize);
	std::vector<ImageRGB> resizeImage(ImageRGB& image, const Size& targetSize);

	void enableDebugMode();
	void disableDebugMode();

private:
	bool isMaskLegal(const ImageRGB& image, const ImageRGB& mask);

	bool isDebugEnabled();

	std::vector<ImageRGB> chooseStrategy(ImageRGB& image, ImageGray& energyMap, const Size& targetSize);

	ImageGray createCummulativeEnergyMap(const ImageGray& energyMap, Orientation orientation);
	std::vector<Orientation> getRemovalOrder(int rowsToRemove, int colsToRemove);

	Seam findSeam(const ImageGray& cummulativeEnergyMap, Orientation orientation);
	void insertSeams(ImageRGB& image, ImageGray& energyMap, const Size& targetSize);
	std::vector<ImageRGB> removeSeams(ImageRGB& image, ImageGray& energyMap, const Size& targetSize);

	std::unique_ptr<EnergyCalculator> m_energyCalculator;
	bool m_debug;
};

#endif
