#include "polynomial.h"

// do not change this function
template< typename T, int N > 
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
