#include "../Include/ImageProcessor.hpp"

void ImageProcessor::removeAlphaChannel(Image & image)
{
	if (image.getNChannels() == 1 || image.getNChannels() == 3)
		return;

	Image withoutAlpha;
	withoutAlpha.setProperties(image.getWidth(), image.getHeight(), image.getNChannels() - 1);

	int oldIndex = 0;
	int newIndex = 0;

	unsigned char * newData = withoutAlpha.getData();
	unsigned char * oldData = image.getData();

	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			for (int c = 0; c < withoutAlpha.getNChannels(); c++) {
				newData[newIndex + c] = oldData[oldIndex + c];
			}
			newIndex += withoutAlpha.getNChannels();
			oldIndex += image.getNChannels(); 
		}
	}

	image = withoutAlpha;
}

void ImageProcessor::convertToGrayscale(Image & image)
{
	if (image.getNChannels() % 2 == 0)
		removeAlphaChannel(image);
	if (image.getNChannels() == 1)
		return;

	Image gray;
	gray.setProperties(image.getWidth(), image.getHeight(), 1);

	unsigned char* newData = gray.getData();
	unsigned char* oldData = image.getData();

	int oldIndex = 0;
	int grayIndex = 0;

	Color color;
	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			color.setColor(oldData[oldIndex], oldData[oldIndex + 1], oldData[oldIndex + 2]);
			newData[grayIndex] = Color::calculateIntensity(color)*255;
			oldIndex += 3;
			grayIndex += 1;
		}
	}

	image = gray;
}

void ImageProcessor::medianCut(Image & img, Palette palette)
{
}

void ImageProcessor::floydStainberg(Image & img, Palette palette)
{
}
