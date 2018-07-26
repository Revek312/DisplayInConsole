#ifndef DIC_CONSOLE_HPP
#define DIC_CONSOLE_HPP

#include "Image.hpp"
#include <Windows.h>

class Console {
public:
	
	static void setConsoleSize(int width, int height);
	static void setConsoleFont(int size);
	static void setConsolePalette(Palette palette);

	static void display(Image& indexed);
};

#endif