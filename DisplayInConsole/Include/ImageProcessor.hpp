#ifndef DIC_IMAGEPROCESSOR_HPP
#define DIC_IMAGEPROCESSOR_HPP

#include "Image.hpp"
#include "Box.hpp"

class ImageProcessor {
public:

	static void removeAlphaChannel(Image& image);
	static void convertToGrayscale(Image& image, Palette& palette);

	// Methods for calculating palettes
	static void medianCut(Image& img, Palette& palette, int paletteSize = 16);

	// Methods for mapping and diathering
	static void mapFloydStainberg(Image& img, Palette& palette);
	static void mapNoDiather(Image& image, Palette& palette);

	static void quicksort(unsigned char* data, size_t size);
};

#endif