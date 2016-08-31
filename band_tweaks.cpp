#include "band_tweaks.h"

namespace band_tweaks {

    extern "C"{
        // FORTRAN adds _ after all the function names and all variables are called by reference
        // reference: https://ubuntuforums.org/showthread.php?t=1740797
        void dgbmv_ (
            const char * TRANS,
            const int * M,
            const int * N,
            const int * KL,
            const int * KU,
            const double * ALPHA,
            const double * A,
            const int * LDA,
            const double * X,
            const int * INCX,
            const double * BETA,
            double * Y,
            const int * INCY
        );
    }

    VectorXd mult (const BandMatrix<double> & B, const VectorXd & v) {
        const int m = B.rows();
        const int n = B.cols();
        const int subs = B.subs();
        const int supers = B.supers();
        VectorXd w (m);
        const char transpose = 'N';
        const int increment = 1;
        const double scalar_mult  = 1;
        double zero = 0;
        int lda = subs+supers+1;
        dgbmv_(&transpose,
               &m, &n, &subs, &supers,
               &scalar_mult,
               B.coeffs().data(),
               &lda,
               v.data(),
               &increment,
               &zero,
               w.data(),
               &increment);
        return w;
    }

}
