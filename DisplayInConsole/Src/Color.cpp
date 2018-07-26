#include "..\Include\Color.hpp"

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	r_ = r;
	g_ = g;
	b_ = b;
}

Color::~Color()
{
}

unsigned char Color::getR()
{
	return r_;
}

unsigned char Color::getG()
{
	return g_;
}

unsigned char Color::getB()
{
	return b_;
}

void Color::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	r_ = r;
	g_ = g;
	b_ = b;
}

// Euclidean distance between colors

double Color::calculateDistance(Color& c1, Color& c2)
{
	// Calculate difference between rgb colors
	int redDifference	= static_cast<int>(c2.getR() - c1.getR());
	int greenDifference = static_cast<int>(c2.getG() - c1.getG());
	int blueDifference	= static_cast<int>(c2.getB() - c1.getB());

	double distance = sqrt(	redDifference*redDifference + 
							greenDifference * greenDifference + 
							blueDifference * blueDifference	);

	return distance;
}

// Colorimetric conversion to grayscale

double Color::calculateIntensity(Color& color)
{
	double redWeight = 0.2126;
	double greenWeight = 0.7152;
	double blueWeight = 0.0722;
	double gamma = 2.0;

	// Array to store linear RGB values [r][g][b];
	double linearIntensity[3] = {color.getR(), color.getG(), color.getB()};

	for (int i = 0; i < 3; i++) {

		// Values need to be in [0,1] range
		linearIntensity[i] /= 255;

		// Calculate gamma expansion

		if (linearIntensity[i] <= 0.04045) {
			linearIntensity[i] /= 12.92;
		}
		else {
			linearIntensity[i] = pow((linearIntensity[i] + 0.055) / 1.055, 2.4);
		}
	}

	// Calculate linear luminance

	double linearLuminance = redWeight * linearIntensity[0] + greenWeight * linearIntensity[1] + blueWeight * linearIntensity[2];

	double compressedLuminance;

	// Gamma compress linear luminance

	if (linearLuminance <= 0.0031308)
		compressedLuminance = 12.92 * linearLuminance;
	else
		compressedLuminance = 1.055 * pow(linearLuminance, 1.0 / 2.4) - 0.055;

	return compressedLuminance;
}



int Color::findClosestColorInPalette(Color& color, Palette& palette)
{
	double shortestDistance = DBL_MAX;
	double distance = 0;
	int index = 0;

	for (int i = 0; i < palette.size(); i++) {
		distance = Color::calculateDistance(color, palette[i]);

		if (distance < shortestDistance) {
			shortestDistance = distance;
			index = i;
		}

	}

	return index;
}
