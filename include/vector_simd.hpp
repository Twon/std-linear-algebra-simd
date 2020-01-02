//
// Created by Antony Peacock on 20/12/2019.
//

#ifndef LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP

#pragma once

#include <experimental/simd>
#include <initializer_list>

namespace linear_algebra {


//    template<class T, int32_t R, int32_t C>
//    using fs_matrix = matrix<fs_matrix_engine<T, R, C>>;

    class fs_vector4f_simd_engine
    {
    public:
        using engine_category = STD_LA::mutable_vector_engine_tag;
        using element_type    = float;
        using value_type      = float;
        using reference       = float&;
        using pointer         = float*;
        using const_reference = float const&;
        using const_pointer   = float const*;
        using iterator        = STD_LA::detail::vector_iterator<fs_vector4f_simd_engine>;
        using const_iterator  = STD_LA::detail::vector_const_iterator<fs_vector4f_simd_engine>;
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
        constexpr fs_vector4f_simd_engine();
        template<class U>
        constexpr fs_vector4f_simd_engine(std::initializer_list<U> list);
        constexpr fs_vector4f_simd_engine(float, float) noexcept;

        constexpr fs_vector4f_simd_engine(fs_vector4f_simd_engine&&) noexcept = default;
        constexpr fs_vector4f_simd_engine(fs_vector4f_simd_engine const&) = default;

        constexpr fs_vector4f_simd_engine& operator =(fs_vector4f_simd_engine&&) noexcept = default;
        constexpr fs_vector4f_simd_engine& operator =(fs_vector4f_simd_engine const&) = default;

        constexpr const_reference   operator ()(index_type i) const;
        constexpr const_iterator    begin() const noexcept;
        constexpr const_iterator    end() const noexcept;

        constexpr size_type     capacity() const noexcept;
        constexpr index_type    elements() const noexcept;
        constexpr size_type     size() const noexcept;

        constexpr reference     operator ()(index_type i);
        constexpr iterator      begin() noexcept;
        constexpr iterator      end() noexcept;

        constexpr void  swap(fs_vector4f_simd_engine& rhs) noexcept;
        constexpr void  swap_elements(index_type i, index_type j) noexcept;

    private:
        alignas(16) float ma_elems[4];
    };

    inline constexpr fs_vector4f_simd_engine::fs_vector4f_simd_engine()
    :   ma_elems()
    {
    }

    template<class U>
    inline constexpr fs_vector4f_simd_engine::fs_vector4f_simd_engine(std::initializer_list<U> list)
    :   ma_elems()
    {
        size_t  total = (size_t)(4);
        size_t  count = std::min(total, list.size());
        auto    iter  = list.begin();

        for (size_t i = 0;  i < count;  ++i, ++iter)
        {
            ma_elems[i] = static_cast<float>( *iter);
        }

        if (count < total)
        {
            for (size_t i = count;  i < total;  ++i)
            {
                ma_elems[i] = static_cast<float>(0);
            }
        }
    }

    inline constexpr typename fs_vector4f_simd_engine::const_reference
    fs_vector4f_simd_engine::operator ()(index_type i) const
    {
        return ma_elems[i];
    }

    inline constexpr typename fs_vector4f_simd_engine::const_iterator
    fs_vector4f_simd_engine::begin() const noexcept
    {
        return const_iterator(this, 0, 4);
    }

    inline constexpr typename fs_vector4f_simd_engine::const_iterator
    fs_vector4f_simd_engine::end() const noexcept
    {
        return const_iterator(this, 4, 4);
    }

    inline constexpr typename fs_vector4f_simd_engine::size_type
    fs_vector4f_simd_engine::capacity() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_vector4f_simd_engine::index_type
    fs_vector4f_simd_engine::elements() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_vector4f_simd_engine::size_type
    fs_vector4f_simd_engine::size() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_vector4f_simd_engine::reference
    fs_vector4f_simd_engine::operator ()(index_type i)
    {
        return ma_elems[i];
    }

    inline constexpr typename fs_vector4f_simd_engine::iterator
    fs_vector4f_simd_engine::begin() noexcept
    {
        return iterator(this, 0, 4);
    }

    inline constexpr typename fs_vector4f_simd_engine::iterator
    fs_vector4f_simd_engine::end() noexcept
    {
        return iterator(this, 4, 4);
    }

    inline constexpr void
    fs_vector4f_simd_engine::swap(fs_vector4f_simd_engine& rhs) noexcept
    {
        if (&rhs != this)
        {
            for (index_type i = 0;  i < 4;  ++i)
            {
                STD_LA::detail::la_swap(ma_elems[i], rhs.ma_elems[i]);
            }
        }
    }

    inline constexpr void
    fs_vector4f_simd_engine::swap_elements(index_type i, index_type j) noexcept
    {
        STD_LA::detail::la_swap(ma_elems[i], ma_elems[j]);
    }

    /// Alias for a fixed size vector type implemented using simd instructions.
    using vector4 = STD_LA::vector<fs_vector4f_simd_engine>;

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
