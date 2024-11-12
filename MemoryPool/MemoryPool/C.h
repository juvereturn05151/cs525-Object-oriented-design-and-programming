#pragma once
#include"MemoryPool.h"

class C
{
private:
    int data;
    static MemoryPool<C> pool;
public:
    C(int x) : data(x) {}
    void* operator new(size_t size); 
    void operator delete(void* ptr);
};

