#include "band_tweaks.h"

namespace band_tweaks {

	// utils
	
    namespace util {

        template <typename M>
        uint supers (const MatrixBase<M> & A) {
            const uint n = A.cols();
            int d;
            for (d = n-1; d > 0; --d) {
                if (!(A.diagonal(d).array() == 0).all())
                    break;
            }
            return d;
        }

        template <typename M>
        uint subs (const MatrixBase<M> & A) {
            const uint m = A.rows();
            int d;
            for (d = -m+1; d < 0; ++d) {
                if (!(A.diagonal(d).array() == 0).all())
                    break;
            }
            return -d;
        }

    }
	
	// conversion
    template <typename M>
    BandMatrix<typename M::Scalar> fromDenseMatrix(const MatrixBase<M> & A, const uint supers, const uint subs) {
        BandMatrix<typename M::Scalar> B (A.rows(), A.cols(), supers, subs);
        for (int i = -subs; i <= static_cast<int>(supers); ++i) {
            B.diagonal(i) = A.diagonal(i);
        }
        return B;
    }

    template <typename M>
    BandMatrix<typename M::Scalar> fromDenseMatrix(const MatrixBase<M> & A) {
        return fromDenseMatrix(A, util::supers(A), util::subs(A));
    }

    // slicing

	template <typename Scalar>
	double & item (BandMatrix<Scalar> & B, const uint i, const uint j) {
		eigen_assert(
			// 0 <= i && // enforced by type
			// j-B.supers() <= i && // enforced by storage format
			i < B.rows() &&
			i <= j+B.subs()
		);
		return B.coeffs()(B.supers()+i-j, j);
	}

	template <typename Scalar>
	auto slice (BandMatrix<Scalar> & B, const uint row, const std::tuple<uint, int> & col_range) {
		const uint from = std::get<0>(col_range);
		const int to    = std::get<1>(col_range);
		const uint len  = to-from+1;
		auto sliced_row =  B.coeffs().rowwise().reverse().diagonal(B.cols()-B.supers()-row-1).transpose().reverse();
		eigen_assert(
			len == 0 || (
			// 0 <= row &&
			row < B.rows() // &&
			// 0 <= from &&
			// row-B.subs() <= from &&
			// to < B.cols() &&
			// to <= row+B.supers()
		));
		const uint row_start = std::max<int>(row-B.subs(), 0);
		return sliced_row.segment(from-row_start, len);
	}

	template <typename Scalar>
	auto slice (BandMatrix<Scalar> & B, const std::tuple<uint, int> & row_range, const uint col) {
		const uint from = std::get<0>(row_range);
		const int to    = std::get<1>(row_range);
		const uint len  = to-from+1;
		eigen_assert(
			len == 0 || (
			// 0 <= col &&
			// col < B.cols() &&
			// 0 <= from &&
			col-B.supers() <= from &&
			to < B.rows() &&
			to <= col+B.subs()
		));
		
		return B.coeffs().template block<Dynamic, 1>(B.supers()+from-col, col, len, 1);
	}
	
	// operations
	
	template <typename Scalar>
    BandMatrix<Scalar> transpose(const BandMatrix<Scalar> & B) {
        BandMatrix<Scalar> Bt (B.cols(), B.rows(), B.subs(), B.supers());
        for (int i = -B.supers(); i <= B.subs(); ++i) {
            Bt.diagonal(i) = B.diagonal(-i);
        }
        return Bt;
    }


}
