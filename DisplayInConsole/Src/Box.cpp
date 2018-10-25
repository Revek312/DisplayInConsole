#include "../Include/Box.hpp"

char Box::dominantChannel()
{
	long rSum = 0;
	long gSum = 0;
	long bSum = 0;

	for (int i = 0; i < pixels.size(); i++) {
		rSum += pixels[i].getR();
		gSum += pixels[i].getG();
		bSum += pixels[i].getB();
	}

	return rSum > gSum ?
		(rSum > bSum ? 0 : 2) :
		(gSum > bSum ? 1 : 2);

}

void Box::split(Box & l, Box & r)
{
	l.pixels.clear();
	r.pixels.clear();

	char dominant = dominantChannel();
	int median;

	if (dominant == 0) 
		std::sort(pixels.begin(), pixels.end(), [](Color& a, Color& b) {return a.r_ < b.r_; });
	if (dominant == 1)
		std::sort(pixels.begin(), pixels.end(), [](Color& a, Color& b) {return a.g_ < b.g_; });
	else
		std::sort(pixels.begin(), pixels.end(), [](Color& a, Color& b) {return a.b_ < b.b_; });
	
	size_t halfPosition = pixels.size() / 2;

	l.pixels.assign(pixels.begin(), pixels.begin() + halfPosition);
	r.pixels.assign(pixels.begin() + halfPosition, pixels.end());
}

Color Box::averageColor()
{
	long red = 0;
	long green = 0;
	long blue = 0;

	for (int i = 0; i < pixels.size(); i++) {
		red += pixels[i].getR();
		green += pixels[i].getG();
		blue += pixels[i].getB();
	}

	red /= pixels.size();
	green /= pixels.size();
	blue /= pixels.size();
	Color average(red, green, blue);

	return average;
}
