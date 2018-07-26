#include <vector>
#include <math.h>
#include <limits>
class Color;

typedef std::vector<Color> Palette;

// Store rgb values and suppy some 
// useful functions

class Color
{
public:

	Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
	~Color();

	unsigned char getR();
	unsigned char getG();
	unsigned char getB();

	void setColor(unsigned char r, unsigned char g, unsigned char b);

	static double calculateDistance(Color& c1, Color& c2);
	static double calculateIntensity(Color& color);
	static int findClosestColorInPalette(Color& color, Palette& palette);

private:

	unsigned char r_;
	unsigned char g_;
	unsigned char b_;

};

