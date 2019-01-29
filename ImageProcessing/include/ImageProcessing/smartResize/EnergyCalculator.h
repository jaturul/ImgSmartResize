#ifndef ENERGY_CALCULATOR_H
#define ENERGY_CALCULATOR_H

#include "ImageProcessing/containers/ImageRGB.h"
#include "ImageProcessing/containers/ImageGray.h"

class EnergyCalculator
{
public:

	static ImageGray calculateEnergy(const ImageRGB& image);
	static ImageGray calculateEnergy(const ImageRGB& image, const ImageRGB& mask);

private:

};

#endif
