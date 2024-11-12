#include"MemoryPool.h"

template <typename T>
MemoryPool<T>::MemoryPool(size_t _allocatedAmount) : objectSize(sizeof(T)), allocatedAmount(_allocatedAmount)
{
	AllocateChunk();
}

/*
Create an iterator and free each allocated chunk
*/
template <typename T>
MemoryPool<T>::~MemoryPool() 
{
	typename std::vector<void*>::iterator it;

	for (it = allocatedChunks.begin(); it != allocatedChunks.end(); ++it)
	{
		std::free(*it);
	}
}

/*
Allocate a chunk with objectSuze * allocatedAmount
Create a free block according to the i * _objectSize
*/
template <typename T>
void MemoryPool<T>::AllocateChunk()
{
	void* newChunk = malloc(objectSize * allocatedAmount);
	allocatedChunks.push_back(newChunk);

	for (size_t i = 0; i < allocatedAmount; ++i)
	{
		void* memoryBlock = static_cast<char*>(newChunk) + (i * objectSize);
		freeMemories.push(memoryBlock);
	}
}

/*
if there is nothing, allocate a new chunk
return the upper most block of memory
*/
template <typename T>
T* MemoryPool<T>::AllocateMemory() 
{
	if (freeMemories.empty())
	{
		AllocateChunk();
	}

	void* obj = freeMemories.top();
	freeMemories.pop();
	return static_cast<T*>(obj);
}

/*
When we free an object, we add to the stack
*/
template <typename T>
void MemoryPool<T>::FreeMemory(T* obj)
{
	freeMemories.push(obj);
}