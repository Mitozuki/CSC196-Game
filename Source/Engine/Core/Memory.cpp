#include "Memory.h"
#include <iostream>

using namespace std;

void* operator new (size_t size)
{
	cout << "allocated: " << size << endl;

	return malloc(size);
}
void operator delete (void* address, size_t size)
{
	cout << "deallocated: " << size << endl;

	free(address);
}