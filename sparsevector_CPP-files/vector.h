#ifndef VECTOR_H
#define VECTOR_H

#include <fstream>
#include <iostream>

namespace CS225 {
    // Forward declaration of the SparseVector class
    class SparseVector;

    class ElementProxy {
    public:
        ElementProxy(SparseVector& v, long pos);

        operator int() const;
        ElementProxy& operator=(int value);
        ElementProxy& operator+=(int value);
        ElementProxy& operator-=(int value);
        ElementProxy& operator=(ElementProxy proxy);

    private:
        SparseVector& v;
        long pos;
    };

    // Define the ElementNode struct
    struct ElementNode {
        int data;
        int pos;
        struct ElementNode* next;
    };

    // Define the SparseVector class
    class SparseVector {
    public:
        SparseVector();
        SparseVector(SparseVector const& rhs);
        SparseVector& operator=(SparseVector rhs);
        ~SparseVector();

        int Get(long pos) const;
        void Insert(int val, long pos);
        void Delete(long pos);

        ElementProxy operator[](long pos);
        int operator[](unsigned int pos) const;
        SparseVector operator+(const SparseVector& rhs) const;
        SparseVector operator+(const long val) const;
        SparseVector operator*(const SparseVector& rhs) const;
        SparseVector operator*(int rhs) const;

        void PrintRaw() const { //used for grading
            ElementNode* curr = pHead;
            std::cout << "Raw vector: ";
            while (curr) {
                std::cout << "(" << curr->data << ", " << curr->pos << ")";
                curr = curr->next;
            }
            std::cout << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const SparseVector& s);
        friend SparseVector operator*(int value, const SparseVector& rhs);

    private:
        ElementNode* pHead;
        long dimension;
    };
}

#endif