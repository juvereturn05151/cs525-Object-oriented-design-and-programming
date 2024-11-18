#include "C.h"
#include <stdio.h>

void test0(void);
void test1(void);
void test2(void);

void test0(void) 
{
    int const size = 100;
    C* a[ size ];
    for ( int i=0; i<size; ++i ) 
    {
        a[i] = new C( i );
    }
}

void test1(void)
{
    int const size = 100;
    C* a[ size ];
    for ( int i=0; i<size; ++i ) 
    {
        a[i] = new C( i );
    }
    //and one more 
    C* p = new C(100);
}

void test2(void)
{
    int const size = 100;
    C* a[ size ];
    for ( int i=0; i<size; ++i ) 
    {
        a[i] = new C( i );
    }
    for ( int i=0; i<size; i+=2 ) 
    {
        delete a[i];
    }
    C* b[ size/2 ];
    for ( int i=0; i<size/2; ++i ) 
    {
        b[i] = new C( i ); // uses blocks that where freed above
    }
}

void (*pTests[])() = { test0, test1, test2 };

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