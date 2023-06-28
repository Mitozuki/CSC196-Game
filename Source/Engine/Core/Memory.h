#pragma once

namespace kiko
{
	struct MemoryAllocation
	{
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker
	{
	public:
		//void Add(void* address, size_t size);
		//void Remove(void* address);
	private:

	};
}