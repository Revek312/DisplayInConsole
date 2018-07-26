#define STB_IMAGE_IMPLEMENTATION
#include "../Include/ImageProcessor.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
	// Image test code
	Image image;
	image.load(std::string("test.png"));
	image.writeData();

	ImageProcessor::convertToGrayscale(image);
	image.writeData();


	return 0;
}