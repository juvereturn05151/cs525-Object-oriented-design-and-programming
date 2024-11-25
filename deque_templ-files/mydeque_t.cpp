#include "mydeque_t.h"
#include <iostream>
#include <stdexcept> // For exceptions
#include <algorithm> // For std::swap
#include <iomanip>
/*
Note: "% capacity" is for wrapping around the deque
*/
namespace DigiPen 
{
    template<typename T>
    Deque<T>::Deque() : b(0), e(0), size(0), capacity(0), array(nullptr) {}

    template<typename T>
    Deque<T>::Deque(Deque const& rhs) : b(0), e(rhs.size), size(rhs.size), capacity(rhs.capacity) 
    {
        array = new T[capacity];
        for (int i = 0; i < size; ++i) 
        {
            array[i] = rhs.array[(rhs.b + i) % rhs.capacity];
        }
    }

    template<typename T>
    Deque<T>& Deque<T>::operator=(Deque rhs) 
    {
        swap(rhs);
        return *this;
    }

    template<typename T>
    Deque<T>::~Deque() 
    {
        delete[] array;
    }

    template<typename T>
    Deque<T>::Deque(T* array_, unsigned int size_) : b(0), e(size_), size(size_), capacity(size_ * 2) 
    {
        array = new T[capacity];
        for (unsigned int i = 0; i < size_; ++i) 
        {
            array[i] = array_[i];
        }
    }

    template<typename T>
    int Deque<T>::Size() const 
    {
        return size;
    }

    template<typename T>
    bool Deque<T>::Empty() const 
    {
        return size == 0;
    }

    template<typename T>
    void Deque<T>::Clear() 
    {
        b = e = size = 0;
    }

    template<typename T>
    int Deque<T>::Capacity() const 
    {
        return capacity;
    }

    template<typename T>
    void Deque<T>::Push_front(T val) 
    {
        if (size == capacity) 
        {
            reallocate(capacity == 0 ? 1 : capacity * 2);
        }

        b = (b - 1 + capacity) % capacity;
        array[b] = val;
        ++size;
    }

    template<typename T>
    T Deque<T>::Pop_front() {
        if (Empty()) 
        {
            throw std::underflow_error("Deque is empty");
        }

        if (size == capacity / 4) 
        { 
            reallocate(capacity / 2);
        }

        T val = array[b];
        b = (b + 1) % capacity;
        --size;
        return val;
    }

    template<typename T>
    void Deque<T>::Push_back(T val) 
    {
        if (size == capacity) 
        {
            //if there is nothing, default to else double the capacity
            reallocate(capacity == 0 ? 1 : capacity * 2);
        }

        array[e] = val;
        e = (e + 1) % capacity;
        ++size;
    }

    template<typename T>
    T Deque<T>::Pop_back() 
    {
        if (Empty()) 
        {
            throw std::underflow_error("Deque is empty");
        }

        if (size == capacity / 4) 
        { 
            reallocate(capacity / 2);
        }

        e = (e - 1 + capacity) % capacity; 
        T val = array[e];                  
        --size;                            // Decrease the size
        return val;    
    }

    template<typename T>
    T& Deque<T>::operator[](unsigned int pos) 
    {
        if (pos >= size) 
        {
            throw std::out_of_range("Index out of range");
        }

        return array[(b + pos) % capacity];
    }

    template<typename T>
    T Deque<T>::operator[](unsigned int pos) const 
    {
        if (pos >= size) 
        {
            throw std::out_of_range("Index out of range");
        }

        return array[(b + pos) % capacity];
    }

    template<typename T>
    void Deque<T>::swap(Deque& other) 
    {
        std::swap(b, other.b);
        std::swap(e, other.e);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        std::swap(array, other.array);
    }

    template<typename T>
    Deque<T>& Deque<T>::operator+=(const Deque& rhs) 
    {
        for (int i = 0; i < rhs.size; ++i) 
        {
            Push_back(rhs[i]);
        }
        return *this;
    }

    template<typename T>
    Deque<T> Deque<T>::operator+(const Deque& rhs) const 
    {
        Deque result(*this);
        result += rhs;
        return result;
    }

    template<typename T>
    Deque<T>& Deque<T>::reverse() 
    {
        for (int i = 0; i < size / 2; ++i) 
        {
            std::swap((*this)[i], (*this)[size - 1 - i]);
        }

        return *this;
    }

    template<typename T>
    Deque<T> Deque<T>::operator~() const {
        Deque result(*this);
        result.reverse();
        return result;
    }

    template<typename T>
    void Deque<T>::Print() const 
    {
        std::cout << "size = " << size << " capacity = " << capacity <<  std::endl;

        if ( array == nullptr ) {
            std::cout << "array=nullptr" << std::endl;
            return;
        }

        // deque may still be empty, but array is allocated, so print some data
        int width = 3;
        // line of indices
        for ( int i=0; i<capacity; ++i ) {
            std::cout << std::setw(width) << i;
        }
        std::cout << " indices" << std::endl;
        // line of data
        for ( int i=0; i<capacity; ++i ) {
            if ( (b<=i and i<e)                         //  ....b.....e.....
                    or (e<b and ( b<=i or i<e) )        //  ....e.....b.....
                    or ( b==e and size>0 ) )            //  ....be.......... either empty or full - look at size
                std::cout << std::setw(width) << array[i];
                else 
                std::cout << std::setw(width) << ".";
        }
        std::cout << " data" << std::endl;

        char ch1 = 'b', ch2 = 'e';
        int dist1 = b+1, dist2 = e-b;
        if( e<b ) {  ch1 = 'e'; ch2 = 'b'; dist1 = e+1; dist2 = b-e; }
        std::cout << std::setw(width*dist1) << ch1;
        std::cout << std::setw(width*dist2) << ch2;
        std::cout << std::endl;
    }

    template<typename T>
    void Deque<T>::reallocate(int new_capacity) 
    {
        // clean - dtor uses this
        if ( new_capacity == 0 ) 
        {
            delete [] array;
            array = nullptr;
            b = 0;
            e = 0;
            size = 0; 
            capacity = 0;

        } else 
        {
            // do not check whether new_capacity makes sense etc - it is caller's responsibility
            T * new_array = new T [new_capacity];
            for ( int i=0;i<size;++i ) 
            {
                new_array[i]=array[(b+i)%capacity]; // new b is 0
            }
            //for (int i=size;i<capacity;++i) new_array[i]=0;
            delete [] array;
            array = new_array;
            b = 0;
            e = size;
            // same size
            capacity = new_capacity;
        }
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, Deque<T> const& d) 
    {
        for (int i = 0; i < d.Size(); ++i) 
        {
            os << d[i] << " ";
        }

        return os;
    }
};