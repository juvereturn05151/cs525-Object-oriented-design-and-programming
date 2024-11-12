#include "C.h"
#include <stdio.h>

void test0(void);

void test0(void) 
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
}

void (*pTests[])() = { test0 };

#include <stdio.h> /* sscanf */
int main (int argc, char ** argv) {
    if (argc >1) {
        int test = 0;
        sscanf(argv[1],"%i",&test);
        pTests[test]();
    }
    return 0;
}

/*Pseudo Code
* Memory Pool should be a static class since it only instantiates once.
Class Memory Pool
private:
 - a vector to store a chunk of memory allocated
 - a vector (or stack) to store a freed memory
public:
Constructor;
Destructor;
Allocate;

Class C:
private:
static Memorypool
public:
operator new
operator delete

*/