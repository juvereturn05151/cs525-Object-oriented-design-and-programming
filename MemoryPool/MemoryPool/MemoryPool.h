#pragma once
/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief: a class that support memory pool.
Preallocate extra memory for future dynamic allocations:
*/

#include<vector>
#include<stack>

template <typename T>
class MemoryPool
{
private:
	size_t objectSize;
	size_t allocatedAmount;
	//Use void* because it can be casted into any data type
	std::vector<void*> allocatedChunks;
	std::stack<void*> freeMemories;

	void AllocateChunk();
public:
	MemoryPool(size_t _allocatedAmount);
	~MemoryPool();
	T* AllocateMemory();
	void FreeMemory(T* obj);
};

#include "MemoryPool_impl.h"
