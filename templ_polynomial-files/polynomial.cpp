#include "polynomial.h"

// Default constructor
template <typename T, int N>
Polynomial<T, N>::Polynomial() 
{
    for (int i = 0; i <= N; ++i) 
    {
        coeff[i] = T();
    }
}

// Conversion constructor
template <typename T, int N>
template <typename U>
Polynomial<T, N>::Polynomial(const Polynomial<U, N>& other) 
{
    for (int i = 0; i <= N; ++i) {
        coeff[i] = static_cast<T>(other.getCoefficient(i));
    }
}

// Access coefficients
template <typename T, int N>
T Polynomial<T, N>::getCoefficient(int index) const 
{
    return coeff[index];
}

// Modifiable access
template <typename T, int N>
T& Polynomial<T, N>::operator[](unsigned int index) 
{
    if (index > N) {
        throw std::out_of_range("Index out of range");
    }

    return coeff[index];
}

// Read-only access
template <typename T, int N>
T Polynomial<T, N>::operator[](unsigned int index) const 
{
    if (index > N) {
        throw std::out_of_range("Index out of range");
    }

    return coeff[index];
}

// Evaluate polynomial at a value
template <typename T, int N>
T Polynomial<T, N>::operator()(T x) const 
{
    T result = 0;
    T power = 1;

    for (int i = 0; i <= N; ++i) {
        result += coeff[i] * power;
        power *= x;
    }

    return result;
}

// Operator* implementation
template <typename T, int N, int K>
Polynomial<T, N + K> operator*(const Polynomial<T, N>& lhs, const Polynomial<T, K>& rhs) 
{
    Polynomial<T, N + K> result;

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            result.coeff[i + j] += lhs.coeff[i] * rhs.coeff[j];
        }
    }

    return result;
}

// Operator<< implementation
template <typename T, int N>
std::ostream& operator<<(std::ostream& out, const Polynomial<T, N>& pol) 
{
    out << pol.coeff[0] << " ";
    for (int i = 1; i <= N; ++i) {
        if (pol.coeff[i] != 0) { // skip terms with zero coefficients
            if (pol.coeff[i] > 0) {
                out << "+";
            }

            if (pol.coeff[i] == 1) {
            } else if (pol.coeff[i] == -1) {
                out << "-";
            } else {
                out << pol.coeff[i] << "*";
            }
            out << "x^" << i << " ";
        }
    }
    return out;
}