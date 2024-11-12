#include"C.h"

int main() 
{
    int const size = 100;
    C* a[size];

    //Case 1: Allocate objects
    for (int i = 0; i < size; ++i) 
    {
        a[i] = new C(i);
    }

    //Case 2: Allocate an additional object beyond initial size
    C* p = new C(100);

    //Case 3: Reuse freed blocks
    for (int i = 0; i < size; i += 2) 
    {
        delete a[i]; 
    }
    
    C* b[size / 2];

    // Should reuse freed memory
    for (int i = 0; i < size / 2; ++i) 
    {
        b[i] = new C(i + 200); 
    }

    // Cleanup remaining allocations
    for (int i = 1; i < size; i += 2) 
    {
        delete a[i];
    }

    delete p;
    
    for (int i = 0; i < size / 2; ++i) 
    {
        delete b[i];
    }

	return 0;
}

/*Pseudo Code
* Memory Pool should be a static class since it only instantiates once.
Class Memory Pool
private:
Member:
 - a vector to store a chunk of memory allocated
 - a vector (or stack) to store a freed memory
public:
Constructor;
Destructor;
Allocate;

Class C:
Member:
static Memorypool

*/