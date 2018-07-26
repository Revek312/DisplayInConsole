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

void ImageProcessor::convertToGrayscale(Image & image, Palette& palette)
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

	int val = 0;
	palette.clear();
	for (int i = 0; i < 16; i++) {
		palette.push_back(Color(val, val, val));
		val += 17;
	}
}

void ImageProcessor::medianCut(Image & image, Palette& palette, int paletteSize)
{
	std::vector <Box> boxes;
	Box box;
	Color color;

	unsigned char* data = image.getData();
	int index = 0;

	// Load all pixels to first box

	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			color.setColor(data[index], data[index + 1], data[index + 2]);
			index += 3;
			box.pixels.push_back(color);
		}
	}

	boxes.push_back(box);

	std::vector<Box> newBoxes;
	Box left;
	Box right;

	while (boxes.size() < paletteSize) {
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i].split(left, right);
			newBoxes.push_back(left);
			newBoxes.push_back(right);
		}
		boxes.swap(newBoxes);
		newBoxes.clear();
	}

	palette.clear();
	for (int i = 0; i < boxes.size(); i++) {
		palette.push_back(boxes[i].averageColor());
	}

}

void ImageProcessor::mapFloydStainberg(Image & image, Palette& palette)
{
}

void ImageProcessor::mapNoDiather(Image & image, Palette & palette)
{
	Image indexed;
	indexed.setProperties(image.getWidth(), image.getHeight(), 1);

	unsigned char * data = image.getData();
	unsigned char * map = indexed.getData();

	int dataIndex = 0;
	int indexIndex = 0;
	int maped;
	Color color;

	for(int y = 0; y < image.getHeight(); y++){
		for (int x = 0; x < image.getWidth(); x++) {

			// Gray image
			if (image.getNChannels() == 1) {
				color.setColor(data[dataIndex], data[dataIndex], data[dataIndex]);
				dataIndex += 1;
			}

			// Color image
			else {
				color.setColor(data[dataIndex], data[dataIndex + 1], data[dataIndex + 2]);
				dataIndex += 3;
			}

			maped = Color::findClosestColorInPalette(color, palette);
			map[indexIndex] = maped;
			indexIndex++;
		}
	}

	image = indexed;
}