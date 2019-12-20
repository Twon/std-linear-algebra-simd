//
// Created by Antony Peacock on 20/12/2019.
//

#ifndef LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP

#pragma once

#include <experimental/simd>

namespace linear_algebra {

    class vector4 {
    public:

        vector4& operator+(const vector4 rhs);
        vector4& operator-(const vector4 rhs);
        vector4& operator*(const vector4 rhs);
        vector4& operator*(const float rhs);
        vector4& operator%(const vector4 rhs);
        vector4& operator/(const float rhs);
    private:
        std::experimental::parallelism_v2::simd<float> mData;
    };

} // namespace linear_algebra

#endif //LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP
