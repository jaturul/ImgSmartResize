#ifndef ENERGY_CALCULATOR_H
#define ENERGY_CALCULATOR_H

#include "ImageProcessing/containers/ImageRGB.h"
#include "ImageProcessing/containers/ImageGray.h"
#include "ImageProcessing/smartResize/ImageCalculator.h"

class EnergyCalculator
{
public:

	ImageGray calculateEnergy(const ImageRGB& image);
	ImageGray calculateEnergy(const ImageRGB& image, const ImageRGB& mask);

private:

};

#endif
