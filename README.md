# BandMatrix Tweaks

## Banded matrices

Banded matrices are important as they naturally arise from discretising 1-dimensional PDEs and can be efficiently solved via LU and Cholesky decomposition.

Eigen has some support for banded matrices via the `Eigen::internal::BandMatrix` class. This class stores banded matrices as their diagonals, allowing efficient storage of these sparse matrices.

For details on the storage format see http://www.netlib.org/lapack/lug/node124.html.

## What tweaks?

Since the operations implemented for the `BandMatrix` class are somewhat lacking, the purpose of this library is to add some of those missing features. All contributions are welcome.

Current capabilities are:

* Element access via the `item` function: B(i, j) is `item(B, i, j)`
* Row and column access with the `slice` function: B(i, j:k) is `slice(B, i, {j, k})`, B(i:j, k) is `slice(B, {i, j}, k)`
* Multiplication via the `mult` function: B*b is `mult(B, b)`
* Transposition via the `transpose` function: B^T is `transpose(B)`
* Conversion from dense format via the `fromDenseMatrix` function: use either `fromDenseMatrix(A, supers, subs)` or `fromDenseMatrix(A)` for a dense matrix A.

Please see [tutorial.cpp](tutorial.cpp) a more complete introduction. 



