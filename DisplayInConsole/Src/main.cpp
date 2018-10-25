#define STB_IMAGE_IMPLEMENTATION
#include "../Include/ImageProcessor.hpp"
#include "../Include/Console.hpp"
#include <cstdio>
#include <ctime>

int main(int argc, char *argv[]) {
	Image image;
	Palette palette;
	if(!image.load(std::string("His glorius shirt.png")))
		return -1;

	ImageProcessor::removeAlphaChannel(image);
//	ImageProcessor::convertToGrayscale(image, palette);
	ImageProcessor::medianCut(image, palette, 16);

	Console::setConsolePalette(palette);
	Console::setConsoleFont(1);
	Console::setConsoleSize(image.getWidth(), image.getHeight() / 2);

	ImageProcessor::mapNoDiather(image, palette);
	Console::display(image);
	return 0;
}