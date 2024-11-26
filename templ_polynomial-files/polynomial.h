#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <stdexcept>
#include <cmath> 

template <typename T, int N>
class Polynomial {
private:
    T coeff[N + 1];

public:
    // default constructor
    Polynomial();

    // conversion constructor
    template <typename U>
    Polynomial(const Polynomial<U, N>& other);

    // modifiable access
    T& operator[](unsigned int index);

    // read-only access
    T operator[](unsigned int index) const;

    // evaluate polynomial at a value
    T operator()(T x) const;

    // declare friend operator*
    template <typename U, int P, int Q>
    friend Polynomial<U, P + Q> operator*(const Polynomial<U, P>& lhs, const Polynomial<U, Q>& rhs);

    // friend operator<< for output
    template <typename U, int M>
    friend std::ostream& operator<<(std::ostream& os, const Polynomial<U, M>& poly);
};

// operator* declaration
template <typename T, int N, int K>
Polynomial<T, N + K> operator*(const Polynomial<T, N>& lhs, const Polynomial<T, K>& rhs);

// operator<< declaration
template <typename T, int N>
std::ostream& operator<<(std::ostream& out, const Polynomial<T, N>& pol);

#include "polynomial.cpp" // Include implementation for templates
#endif // POLYNOMIAL_H