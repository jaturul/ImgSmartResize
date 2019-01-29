#ifndef SEAM_CARVER_H
#define SEAM_CARVER_H

#include "ImageProcessing/containers/ImageRGB.h"
#include "ImageProcessing/containers/ImageGray.h"
#include "ImageProcessing/containers/Size.h"
#include "ImageProcessing/containers/Seam.h"
#include "ImageProcessing/containers/Orientation.h"



class SeamCarver
{
public:
	static void resizeImage(ImageRGB& image, ImageRGB& mask, const Size& targetSize);
	static void resizeImage(ImageRGB& image, const Size& targetSize);
	//TODO - RESIZE IMAGE GRAY!!!!

private:
	static ImageGray createCummulativeEnergyMap(const ImageGray& energyMap, Orientation orientation);
	static std::vector<Orientation> getRemovalOrder(int rowsToRemove, int colsToRemove);

	static Seam findSeam(const ImageGray& cummulativeEnergyMap, Orientation orientation);
	static void removeSeams(ImageRGB& image, ImageGray& energyMap, const Size& targetSize);
};

#endif
