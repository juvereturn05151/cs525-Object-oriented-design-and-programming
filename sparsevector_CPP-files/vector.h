#ifndef DEQUE_H
#define DEQUE_H
#include <fstream>
#include <iostream>

namespace CS225
{
    struct ElementNode 
    {
        int data;
        int pos;
        struct ElementNode *next;
    }; 

    class SparseVector
    {
        public:
            SparseVector();
            SparseVector( SparseVector const& rhs );
            SparseVector& operator=(SparseVector rhs);
            ~SparseVector();

            int Get(long pos) const;
            void Insert(int val, long pos);
            void Delete(long pos);

            int&  operator[](unsigned int pos) ;
            int   operator[](unsigned int pos) const ;
            SparseVector operator+(const SparseVector& rhs) const; 
            SparseVector operator*(const SparseVector& rhs) const; 
            int operator*(const int rhs) const; 

            void PrintRaw () const { //used for grading 
                ElementNode* curr=pHead; 
                std::cout << "Raw vector: "; 
                while (curr) { 
                    std::cout << "(" << curr->data << ", " << curr->pos << ")"; 
                    curr=curr->next; 
                } 
                std::cout << std::endl; 
            }

            friend std::ostream & operator<<(std::ostream & os, const SparseVector &s);
        private:
            ElementNode* pHead;
            long dimension;
    };

    class ElementProxy {
    public:
        ElementProxy(SparseVector& v, long pos) : v(v), pos(pos) {}
        
        operator int() const 
        {
            return v.Get(pos); 
        }
        

        ElementProxy& operator=(int value)
        {
            v.Insert(pos, value);  
            return *this;
        }

    private:
        SparseVector &v;  
        long pos;        
    };

};


#endif