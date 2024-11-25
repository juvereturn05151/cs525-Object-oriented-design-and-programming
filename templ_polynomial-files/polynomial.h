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
    // Default constructor
    Polynomial() 
    {
        for (int i = 0; i <= N; ++i) 
        {
            coeff[i] = T();
        }
    }

    // conversion constructor
    template <typename U>
    Polynomial(const Polynomial<U, N>& other) 
    {
        for (int i = 0; i <= N; ++i) 
        {
            coeff[i] = static_cast<T>(other.getCoefficient(i));
        }
    }

    // Access coefficients
    T getCoefficient(int index) const {
        return coeff[index];
    }

    // Modifiable access
    T& operator[](unsigned int index) {
        if (index > N) {
            throw std::out_of_range("Index out of range");
        }
        return coeff[index];
    }

    // Read-only access
    const T& operator[](unsigned int index) const {
        if (index > N) {
            throw std::out_of_range("Index out of range");
        }
        return coeff[index];
    }

    // Evaluate polynomial at a value
    T operator()(T x) const {
        T result = 0;
        T power = 1;

        for (int i = 0; i <= N; ++i) {
            result += coeff[i] * power;
            power *= x;
        }

        return result;
    }

    // Declare friend operator*
    template <typename U, int P, int Q>
    friend Polynomial<U, P + Q> operator*(const Polynomial<U, P>& lhs, const Polynomial<U, Q>& rhs);

    // Friend operator<< for output
    template <typename U, int M>
    friend std::ostream& operator<<(std::ostream& os, const Polynomial<U, M>& poly);
};

// Operator* implementation
template <typename T, int N, int K>
Polynomial<T, N + K> operator*(const Polynomial<T, N>& lhs, const Polynomial<T, K>& rhs) 
{
    Polynomial<T, N + K> result;

    for (int i = 0; i <= N; ++i) 
    {
        for (int j = 0; j <= K; ++j) 
        {
            result.coeff[i + j] += lhs.coeff[i] * rhs.coeff[j];
        }
    }

    return result;
}

// Operator<< for output
template <typename T, int N>
std::ostream& operator<<(std::ostream& os, const Polynomial<T, N>& poly) 
{
    os << poly.coeff[0];
    for (int i = 1; i <= N; ++i) 
    {
        if (poly.coeff[i] != 0) 
        {
            os << (poly.coeff[i] > 0 ? " + " : " - ") << std::abs(poly.coeff[i]) << "x^" << i;
        }
    }
    return os;
}

#endif // POLYNOMIAL_H