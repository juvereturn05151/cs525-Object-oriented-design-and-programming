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

    // access coefficients
    T getCoefficient(int index) const 
    {
        return coeff[index];
    }

    // modifiable access
    T& operator[](unsigned int index) 
    {
        if (index > N) 
        {
            throw std::out_of_range("Index out of range");
        }

        return coeff[index];
    }

    // read-only access
    T operator[](unsigned int index) const 
    {
        if (index > N) 
        {
            throw std::out_of_range("Index out of range");
        }

        return coeff[index];
    }

    // evaluate polynomial at a value
    T operator()(T x) const 
    {
        T result = 0;
        T power = 1;

        for (int i = 0; i <= N; ++i) 
        {
            result += coeff[i] * power;
            power *= x;
        }

        return result;
    }

    // declare friend operator*
    template <typename U, int P, int Q>
    friend Polynomial<U, P + Q> operator*(const Polynomial<U, P>& lhs, const Polynomial<U, Q>& rhs);

    // friend operator<< for output
    template <typename U, int M>
    friend std::ostream& operator<<(std::ostream& os, const Polynomial<U, M>& poly);
};

// operator* implementation
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

// operator<< for output
template <typename T, int N>
std::ostream& operator<<( std::ostream &out, Polynomial<T, N> const& pol )
{
    out << pol.coeff[0] << " ";
    for ( int i=1;i<=N; ++i ) {
        if ( pol.coeff[i] != 0 ) { // skip terms with zero coefficients
            if      ( pol.coeff[i] > 0 ) {  out << "+"; }

            if      ( pol.coeff[i] == 1 )  { }
            else if ( pol.coeff[i] == -1 ) { out << "-"; }
            else                          { out << pol.coeff[i] << "*"; }
            out << "x^" << i << " ";
        }
    }
    return out;
}

#endif // POLYNOMIAL_H