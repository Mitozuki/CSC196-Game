#include "Memory.h"
#include <iostream>

using namespace std;
kiko::MemoryTracker kiko::g_memoryTracker;

void* operator new (size_t size)
{
	void* p = malloc(size);

	kiko::g_memoryTracker.Add(p, size);

	return p;
}
void operator delete (void* address, size_t size)
{
	kiko::g_memoryTracker.Remove(address, size);
	free(address);
}

namespace kiko
{
	void MemoryTracker::Add(void* address, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocations++;
	}
	void MemoryTracker::Remove(void* address, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocations--;
	}
	void MemoryTracker::DisplayInfo()
	{
		cout << "current bytes allocated: " << m_bytesAllocated << endl;
		cout << "current number of allocations: " << m_numAllocations << endl;
	}
}