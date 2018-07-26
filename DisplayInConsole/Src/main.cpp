#define STB_IMAGE_IMPLEMENTATION
#include "../Include/Image.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
	// Image test code
	Image image;
	image.load(std::string("test.png"));
	image.writeData();
	image.setProperties(4,10,2);
	image.writeData();
	image.load(std::string("test2.png"));
	image.writeData();
	return 0;
}