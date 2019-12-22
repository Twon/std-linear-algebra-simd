#ifndef LINEAR_ALGEBRA_SIMD_QUATERNION_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_QUATERNION_SIMD_HPP

#pragma once

#include <experimental/simd>

namespace linear_algebra {

    class quaternion {
    public:

        quaternion& operator+(const quaternion rhs);
        quaternion& operator-(const quaternion rhs);
        quaternion& operator*(const quaternion rhs);
        quaternion& operator*(const float rhs);
        quaternion& operator%(const quaternion rhs);
        quaternion& operator/(const float rhs);
    private:
        std::experimental::parallelism_v2::simd<float> mData;
    };

} // namespace linear_algebra

#endif //LINEAR_ALGEBRA_SIMD_QUATERNION_SIMD_HPP
