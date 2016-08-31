#ifndef BAND_TWEAKS_H
#define BAND_TWEAKS_H

#include </usr/include/eigen3/Eigen/Dense>
#include <tuple>

namespace band_tweaks {
	
    using namespace Eigen;
    using Eigen::internal::BandMatrix;

    // conversion
    template <typename M>
    BandMatrix<typename M::Scalar> fromDenseMatrix(const MatrixBase<M> & A, const uint supers, const uint subs);

    template <typename M>
    BandMatrix<typename M::Scalar> fromDenseMatrix(const MatrixBase<M> & A);

    // slicing
    template <typename Scalar>
    double & item (BandMatrix<Scalar> & B, const uint i, const uint j);

    template <typename Scalar>
    auto slice (BandMatrix<Scalar> & B, const uint row, const std::tuple<uint, int> & col_range);

    template <typename Scalar>
    auto slice (BandMatrix<Scalar> & B, const std::tuple<uint, int> & row_range, const uint col);

    // operations
    VectorXd mult (const BandMatrix<double> & B, const VectorXd & v);

    template <typename Scalar>
    BandMatrix<Scalar> transpose(const BandMatrix<Scalar> & B);

}

#include "band_tweaks.hpp"

#endif
