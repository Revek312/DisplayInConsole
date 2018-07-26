#ifndef DIC_BOX_HPP
#define DIC_BOX_HPP

#include "Color.hpp"

#include <algorithm>

struct Box {
	std::vector <Color> pixels;

	char dominantChannel();
	void split(Box& l, Box& r);
	Color averageColor();
};

#endif