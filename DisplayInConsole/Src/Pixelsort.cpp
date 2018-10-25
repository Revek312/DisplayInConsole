#include "..\Include\Pixelsort.h"



void Pixelsort::createHeap(unsigned char * data, size_t size)
{
	for (int i = size / 2; i > 0; i--)
		heapify(data, size, i);
}

void Pixelsort::heapify(unsigned char * data, size_t heap_size, int i)
{
	unsigned char largest, temp;
	int l = 2 * i, 
		r = (2 * i) + 1;

	if (l <= heap_size && data[l] > data[i])
		largest = l;
	else largest = i;

	if (r <= heap_size && data[r] > data[largest])
		largest = r;

	if (largest != i) {
		temp = data[largest];
		data[largest] = data[i];
		data[i] = temp;

		heapify(data, heap_size, largest);
	}
}

int Pixelsort::findChannel(unsigned char * data, size_t size)
{
	unsigned char* pt = data+1;
	size_t pix = 0;
	unsigned long r = 0, g = 0, b = 0;
	while (pix < size) {
		r += *(pt - 1);
		g += *pt;
		b += *(pt + 1);

		pt += 2;

		pix++;
	}

	delete pt;

	// r = 0 g = 1 b = 2
	return r > g ? 
		(r > b ? 0 : 2) : 
		(g > b ? 1 : 2) ;
}

Pixelsort::Pixelsort()
{
}


Pixelsort::~Pixelsort()
{
}

void Pixelsort::sort(unsigned char * data, size_t size)
{
	int channel = findChannel(data, size);
	unsigned char temp; 
	createHeap(data, size);

	for (int i = size; i > 1; i--) {
		temp = data[i];
		data[i] = data[1];
		data[1] = temp;
		size--;
		heapify(data, size, 1);
	}
}
