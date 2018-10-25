
class Pixelsort
{
	static void createHeap(unsigned char* data, size_t size);
	static void heapify(unsigned char* data, size_t heap_size, int i);
	static int findChannel(unsigned char* data, size_t size);

public:
	Pixelsort();
	~Pixelsort();

	static void sort(unsigned char* data, size_t size);
};
