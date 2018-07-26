#define STB_IMAGE_IMPLEMENTATION
#include "../Include/ImageProcessor.hpp"
#include "../Include/Console.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
	// Image test code
	Image image;
	Palette palette;

	image.load(std::string("3.png"));

	ImageProcessor::removeAlphaChannel(image);
	ImageProcessor::convertToGrayscale(image, palette);
//	ImageProcessor::medianCut(image, palette, 16);

	Console::setConsolePalette(palette);

	ImageProcessor::mapNoDiather(image, palette);

	Console::display(image);

	return 0;
}