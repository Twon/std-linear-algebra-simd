#ifndef LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP

#pragma once

#include <experimental/simd>
#include <vector_simd.hpp>

namespace linear_algebra {

    /*! \class matrix4

     */
/*    class matrix4 {
    public:

        constexpr matrix4(  const float m00, const float m01, const float m02, const float m03,
                            const float m10, const float m11, const float m12, const float m13,
                            const float m20, const float m21, const float m22, const float m23,
                            const float m30, const float m31, const float m32, const float m33) noexcept;

        constexpr matrix4(  const vector4 m0,
                            const vector4 m1,
                            const vector4 m2,
                            const vector4 m3) noexcept;

        matrix4& operator+(const matrix4 rhs);
        matrix4& operator-(const matrix4 rhs);
        matrix4& operator*(const matrix4 rhs);
        matrix4& operator*(const float rhs);
        matrix4& operator%(const matrix4 rhs);
        matrix4& operator/(const float rhs);
    private:
        std::experimental::parallelism_v2::simd<float> mData[4];
    };*/

    class matrix4_engine
    {
    public:
        using engine_category = la::mutable_matrix_engine_tag;
        using element_type    = float;
        using value_type      = float;
        using reference       = float&;
        using pointer         = float*;
        using const_reference = float const&;
        using const_pointer   = float const*;
        using difference_type = ptrdiff_t;
        using index_type      = int_fast32_t;
        using size_type       = int_fast32_t;
        using size_tuple      = std::tuple<size_type, size_type>;

        using is_fixed_size   = std::true_type;
        using is_resizable    = std::false_type;

        using is_column_major = std::false_type;
        using is_dense        = std::true_type;
        using is_rectangular  = std::true_type;
        using is_row_major    = std::true_type;

        using column_view_type    = la::matrix_column_view<matrix4_engine>;
        using row_view_type       = la::matrix_row_view<matrix4_engine>;
        using transpose_view_type = la::matrix_transpose_view<matrix4_engine>;

    public:
        constexpr matrix4_engine();
        template<class U>
        constexpr matrix4_engine(std::initializer_list<U> list);
        constexpr matrix4_engine(matrix4_engine&&) noexcept = default;
        constexpr matrix4_engine(matrix4_engine const&) = default;

        constexpr matrix4_engine& operator =(matrix4_engine&&) noexcept = default;
        constexpr matrix4_engine& operator =(matrix4_engine const&) = default;

        constexpr const_reference   operator ()(index_type i, index_type j) const;

        constexpr index_type    columns() const noexcept;
        constexpr index_type    rows() const noexcept;
        constexpr size_tuple    size() const noexcept;

        constexpr size_type     column_capacity() const noexcept;
        constexpr size_type     row_capacity() const noexcept;
        constexpr size_tuple    capacity() const noexcept;

        constexpr reference     operator ()(index_type i, index_type j);

        constexpr void      assign(matrix4_engine const& rhs);
        template<class ET2>
        constexpr void      assign(ET2 const& rhs);

        constexpr void      swap(matrix4_engine& rhs) noexcept;
        constexpr void      swap_columns(index_type j1, index_type j2) noexcept;
        constexpr void      swap_rows(index_type i1, index_type i2) noexcept;

    private:
        float   ma_elems[16];
    };

} // namespace linear_algebra

#endif //LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
