#ifndef DIC_IMAGE_HPP
#define DIC_IMAGE_HPP

#include "stb_image.h"
#include "Color.hpp"

#include <string>
#include <conio.h>
class Image {
public:
	Image();
	~Image();

	bool load(std::string fileName);
	bool isReady();
	bool fromStb();

	int getWidth();
	int getHeight();
	int getNChannels();
	unsigned char* getData();

	bool setProperties(int width, int height, int nChannels);

	void writeData();

	Image& operator=(Image& img);
private:

	bool isReady_;
	bool fromStb_;
	
	int width_;
	int height_;
	int nChannels_;

	unsigned char* data_;

	void deleteData();
};

#endif