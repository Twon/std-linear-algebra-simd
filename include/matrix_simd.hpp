#ifndef LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP

#pragma once

#include <experimental/simd>

namespace linear_algebra {

    class matrix4 {
    public:

        matrix4& operator+(const matrix4 rhs);
        matrix4& operator-(const matrix4 rhs);
        matrix4& operator*(const matrix4 rhs);
        matrix4& operator*(const float rhs);
        matrix4& operator%(const matrix4 rhs);
        matrix4& operator/(const float rhs);
    private:
        std::experimental::parallelism_v2::simd<float> mData[4];
    };

} // namespace linear_algebra

#endif //LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
