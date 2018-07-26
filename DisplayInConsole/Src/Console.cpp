#include "../Include/Console.hpp"

void Console::setConsoleSize(int width, int height)
{
	COORD coord;
	coord.X = width;
	coord.Y = height;

	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &Rect);
}

void Console::setConsoleFont(int size)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Console::setConsolePalette(Palette palette)
{
	CONSOLE_SCREEN_BUFFER_INFOEX buffer;

	buffer.cbSize = sizeof CONSOLE_SCREEN_BUFFER_INFOEX;

	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &buffer);

	if (GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &buffer) == 0) {
		printf_s("GetConsoleScreenBufferInfoEx Error: %d", GetLastError());
		return;
	}

	for (int i = 0; i < 16; i++) {
		buffer.ColorTable[i] = RGB(palette[i].getR(), palette[i].getG(), palette[i].getB());
	}

	SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &buffer);

}

void Console::display(Image & indexed)
{
	int halfHeight = indexed.getHeight() / 2 + indexed.getHeight() % 2;
	int bufferIndex = 0;
	unsigned char * data = indexed.getData();

	CHAR_INFO* buffer = new CHAR_INFO[indexed.getWidth() * halfHeight];

	for (int y = 0; y < indexed.getHeight(); y++) {
		for (int x = 0; x < indexed.getWidth(); x++) {
			bufferIndex = (y / 2)*indexed.getWidth() + x;
			if (y % 2 == 0) {
				buffer[bufferIndex].Attributes = (data[y*indexed.getWidth() + x] << 4);
				buffer[bufferIndex].Char.AsciiChar = 220;
			}
			else {
				buffer[bufferIndex].Attributes |= data[y*indexed.getWidth() + x];
			}


		}
	}

	COORD charBuffSize = { indexed.getWidth(), halfHeight };
	COORD characterPos = { 0,0 };
	SMALL_RECT writeArea = { 0,0, indexed.getWidth() - 1, halfHeight - 1 };

	WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, charBuffSize, characterPos, &writeArea);
}
