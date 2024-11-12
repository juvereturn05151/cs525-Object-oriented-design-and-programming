#include "C.h"

MemoryPool<C> C::pool(100);

void* C::operator new(size_t size)
{
	return pool.AllocateMemory();
}

void C::operator delete(void* ptr) 
{
	pool.FreeMemory(static_cast<C*>(ptr));
}