#include <iostream>
#include "band_tweaks.h"

#define EIGEN_INITIALIZE_MATRICES_BY_NAN

int main () {
    using namespace std;
    using namespace band_tweaks;

    // create a 4x4 matrix with two super diagonals, one subdiagonal
    BandMatrix<double> A (4, 4, 2, 1);
    // fill the matrix by its diagonals
    A.diagonal(-1).setConstant(-1);
    A.diagonal(0).segment(0,2).setConstant(1);
    A.diagonal(0).segment(2,2).setConstant(2);
    A.diagonal(1).setConstant(3);
    A.diagonal(2).setConstant(4);
    // we've now initialised all the entries of the matrix
    // let's take a look at what it looks like
    cout << A.toDenseMatrix() << endl << endl;
    // prints 
    //  1  3  4 0
    // -1  1  3 4
    //  0 -1  2 3
    //  0  0 -1 2

    // we can also directly inspect the dense storage format
    cout << A.coeffs() << endl << endl;
    // prints
    //  0  0  4  4
    //  0  3  3  3
    //  1  1  2  2
    // -1 -1 -1  0
    //
    // Note: on some systems, instead of zeros, you might have uninitialised values
    // in the placeholder entries of the coefficient matrix.

    // we have write access too:
    A.coeffs()(1, 1) = 5;
    cout << A.toDenseMatrix() << endl << endl;
    // prints
    //  1  5  4 0
    // -1  1  3 4
    //  0 -1  2 3
    //  0  0 -1 2

    // if you wanna set the actual (1,1) of A
    // you need to adjust your indices

    // let's change (0,1) back to 5 from 3
    item(A, 0, 1) = 3;
    // and change the actual (1,1) to 5
    item(A, 1, 1) = 5;
    cout << A.toDenseMatrix() << endl << endl;
    // prints
    //  1  3  4 0
    // -1  5  3 4
    //  0 -1  2 3
    //  0  0 -1 2

    // finally row and column access:
    // to get A(2, 1:3), ie. all the non-zero elements of the third row
    cout << slice(A, 2, {1, 3}) << endl << endl;
    // let's add 1 to each element of this row
    slice(A, 2, {1, 3}).array() += 1.;
    cout << A.toDenseMatrix() << endl << endl;
    // prints
    //  1 3  4 0
    // -1 5  3 4
    //  0 0  3 4
    //  0 0 -1 2

    // let's swap A(2:3, 2) with A(2:3, 3)
    slice(A, {2, 3}, 2).swap(slice(A, {2, 3}, 3));
    cout << A.toDenseMatrix() << endl << endl;
    // prints
    //  1 3 4  0
    // -1 5 3  4
    //  0 0 4  3
    //  0 0 2 -1
}
