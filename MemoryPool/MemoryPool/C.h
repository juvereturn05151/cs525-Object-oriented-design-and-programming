#pragma once
#include"MemoryPool.h"

class C
{
private:
    int value;
    static MemoryPool<C> pool;
public:
    C(int x);
    void* operator new(size_t size); 
    void operator delete(void* ptr);
};

