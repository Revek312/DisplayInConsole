#include "Image.hpp"
class ImageProcessor {
public:

	static void removeAlphaChannel(Image& image);
	static void convertToGrayscale(Image& image);
	static void medianCut(Image& img, Palette palette);
	static void floydStainberg(Image& img, Palette palette);

private:
	d
};