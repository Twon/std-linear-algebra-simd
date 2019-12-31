#ifndef LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP

#pragma once

#include <experimental/simd>

namespace linear_algebra {

    class vector4_engine
    {
    public:
        using engine_category = la::mutable_vector_engine_tag;
        using element_type    = float;
        using value_type      = float;
        using reference       = float&;
        using pointer         = float*;
        using const_reference = float const&;
        using const_pointer   = float const*;
        using iterator        = la::detail::vector_iterator<vector4_engine>;
        using const_iterator  = la::detail::vector_const_iterator<vector4_engine>;
        using difference_type = ptrdiff_t;
        using index_type      = int_fast32_t;
        using size_type       = int_fast32_t;

        using is_fixed_size   = std::true_type;
        using is_resizable    = std::false_type;

        using is_column_major = std::true_type;
        using is_dense        = std::true_type;
        using is_rectangular  = std::true_type;
        using is_row_major    = std::true_type;

    public:
        constexpr vector4_engine();
        template<class U>
        constexpr vector4_engine(std::initializer_list<U> list);
        constexpr vector4_engine(float, float) noexcept;

        constexpr vector4_engine(vector4_engine&&) noexcept = default;
        constexpr vector4_engine(vector4_engine const&) = default;

        constexpr vector4_engine& operator =(vector4_engine&&) noexcept = default;
        constexpr vector4_engine& operator =(vector4_engine const&) = default;

        constexpr const_reference   operator ()(index_type i) const;
        constexpr const_iterator    begin() const noexcept;
        constexpr const_iterator    end() const noexcept;

        constexpr size_type     capacity() const noexcept;
        constexpr index_type    elements() const noexcept;
        constexpr size_type     size() const noexcept;

        constexpr reference     operator ()(index_type i);
        constexpr iterator      begin() noexcept;
        constexpr iterator      end() noexcept;

        constexpr void  swap(vector4_engine& rhs) noexcept;
        constexpr void  swap_elements(index_type i, index_type j) noexcept;

    private:
        float   ma_elems[4];
    };

/*    class vector4 {
    public:

        constexpr vector4() noexcept;
        constexpr vector4(const float v0, const float v1, const float v2, const float v3) noexcept;

        vector4& operator+(const vector4 rhs);
        vector4& operator-(const vector4 rhs);
        vector4& operator*(const vector4 rhs);
        vector4& operator*(const float rhs);
        vector4& operator%(const vector4 rhs);
        vector4& operator/(const float rhs);
    private:
        std::experimental::parallelism_v2::simd<float> mData;
    };

    inline constexpr vector4::vector4(const float v0, const float v1, const float v2, const float v3) noexcept
//    :   mData{make_vector<std::experimental::parallelism_v2::simd<float>(0, v1, v2, v3)}
    {
    }*/


} // namespace linear_algebra

#endif //LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP
