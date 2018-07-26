#include "..\Include\Image.hpp"

Image::Image()
{
	isReady_ = false;
	fromStb_ = false;
}

Image::~Image()
{
	if (isReady_)
		deleteData();
}

bool Image::load(std::string fileName)
{
	if (isReady_)
		deleteData();

	data_ = stbi_load(fileName.c_str(), &width_, &height_, &nChannels_, 0);

	if (data_ == NULL) {
		isReady_ = false;
		fromStb_ = false;
		return false;
	}

	isReady_ = true;
	fromStb_ = true;

	return true;
}

bool Image::isReady()
{
	return isReady_;
}

bool Image::fromStb()
{
	return fromStb_;
}

int Image::getWidth()
{
	return width_;
}

int Image::getHeight()
{
	return height_;
}

int Image::getNChannels()
{
	return nChannels_;
}

unsigned char * Image::getData()
{
	return data_;
}

bool Image::setProperties(int width, int height, int nChannels)
{
	if (width < 1 || height < 1 || nChannels < 1 || nChannels > 4)
		return false;

	if (isReady_)
		deleteData();

	width_ = width;
	height_ = height;
	nChannels_ = nChannels;

	data_ = nullptr;
	data_ = new unsigned char[width_ * height_ * nChannels_];

	isReady_ = true;
	fromStb_ = false;

	return true;
}

// Writes pixel to console, testing purposes
void Image::writeData()
{
	int index = 0;
	
	for (int y = 0; y < height_; y++) {
		for (int x = 0; x < width_; x++) {
			printf_s("[ ");
			for (int c = 0; c < nChannels_; c++) {
				printf_s("%.3d ", data_[index]);
				index++;
			}
			printf_s("]");
		}
		printf_s("\n");
	}
	printf_s("\n");
}

Image & Image::operator=(Image & img)
{
	setProperties(img.getWidth(), img.getHeight(), img.getNChannels());
	unsigned char* newData = img.getData();

	int index = 0;
	for (int y = 0; y < height_; y++) {
		for (int x = 0; x < width_; x++) {
			for (int c = 0; c < img.getNChannels(); c++) {
				data_[index] = newData[index];
				index++;
			}
		}
	}

//	delete newData;
	return *this;
}

void Image::deleteData()
{
	if (fromStb_) {
		stbi_image_free(data_);
	}
	else {
		delete[] data_;
	}
}
