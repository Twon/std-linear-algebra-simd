#ifndef LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP

#pragma once

#include <experimental/simd>

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

    class fs_matrix4f_simd_engine
    {
    public:
        using engine_category = STD_LA::mutable_matrix_engine_tag;
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

        using column_view_type    = STD_LA::matrix_column_view<fs_matrix4f_simd_engine>;
        using row_view_type       = STD_LA::matrix_row_view<fs_matrix4f_simd_engine>;
        using transpose_view_type = STD_LA::matrix_transpose_view<fs_matrix4f_simd_engine>;

    public:
        constexpr fs_matrix4f_simd_engine();
        template<class U>
        constexpr fs_matrix4f_simd_engine(std::initializer_list<U> list);
        constexpr fs_matrix4f_simd_engine(fs_matrix4f_simd_engine&&) noexcept = default;
        constexpr fs_matrix4f_simd_engine(fs_matrix4f_simd_engine const&) = default;

        constexpr fs_matrix4f_simd_engine& operator =(fs_matrix4f_simd_engine&&) noexcept = default;
        constexpr fs_matrix4f_simd_engine& operator =(fs_matrix4f_simd_engine const&) = default;

        constexpr const_reference   operator ()(index_type i, index_type j) const;

        constexpr index_type    columns() const noexcept;
        constexpr index_type    rows() const noexcept;
        constexpr size_tuple    size() const noexcept;

        constexpr size_type     column_capacity() const noexcept;
        constexpr size_type     row_capacity() const noexcept;
        constexpr size_tuple    capacity() const noexcept;

        constexpr reference     operator ()(index_type i, index_type j);

        constexpr void      assign(fs_matrix4f_simd_engine const& rhs);
        template<class ET2>
        constexpr void      assign(ET2 const& rhs);

        constexpr void      swap(fs_matrix4f_simd_engine& rhs) noexcept;
        constexpr void      swap_columns(index_type j1, index_type j2) noexcept;
        constexpr void      swap_rows(index_type i1, index_type i2) noexcept;

    private:
        alignas(16) float   ma_elems[16];
    };


    inline constexpr fs_matrix4f_simd_engine::fs_matrix4f_simd_engine()
    :   ma_elems()
    {
    }

    template<class U> inline
    constexpr
    fs_matrix4f_simd_engine::fs_matrix4f_simd_engine(std::initializer_list<U> list)
    :   ma_elems()
    {
        size_t  total = (size_t)(4*4);
        size_t  count = min(total, list.size());
        auto    iter  = list.begin();

        for (size_t i = 0;  i < count;  ++i, ++iter)
        {
            ma_elems[i] = static_cast<float>( *iter);
        }
    }

    inline constexpr typename fs_matrix4f_simd_engine::const_reference
    fs_matrix4f_simd_engine::operator ()(index_type i, index_type j) const
    {
        return ma_elems[i*4 + j];
    }

    inline constexpr typename fs_matrix4f_simd_engine::index_type
    fs_matrix4f_simd_engine::columns() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_matrix4f_simd_engine::index_type
    fs_matrix4f_simd_engine::rows() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_matrix4f_simd_engine::size_tuple
    fs_matrix4f_simd_engine::size() const noexcept
    {
        return size_tuple(4, 4);
    }

    inline constexpr typename fs_matrix4f_simd_engine::size_type
    fs_matrix4f_simd_engine::column_capacity() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_matrix4f_simd_engine::size_type
    fs_matrix4f_simd_engine::row_capacity() const noexcept
    {
        return 4;
    }

    inline constexpr typename fs_matrix4f_simd_engine::size_tuple
    fs_matrix4f_simd_engine::capacity() const noexcept
    {
        return size_tuple(4, 4);
    }

    inline
    constexpr typename fs_matrix4f_simd_engine::reference
    fs_matrix4f_simd_engine::operator ()(index_type i, index_type j)
    {
        return ma_elems[i*4 + j];
    }

    inline constexpr void
    fs_matrix4f_simd_engine::assign(fs_matrix4f_simd_engine const& rhs)
    {
        if (&rhs != this) return;

        for (index_type i = 0;  i < 4*4;  ++i)
        {
            ma_elems[i] = rhs.ma_elems[i];
        }
    }

    template<class ET2> inline constexpr void
    fs_matrix4f_simd_engine::assign(ET2 const& rhs)
    {
        using src_index_type = typename ET2::index_type;

        if (rhs.size() != size())
        {
            throw std::runtime_error("invalid size");
        }

        if constexpr(std::is_same_v<index_type, src_index_type>)
        {
            for (index_type i = 0;  i < rows();  ++i)
            {
                for (index_type j = 0;  j < columns();  ++j)
                {
                    (*this)(i, j) = rhs(i, j);
                }
            }
        }
        else
        {
            src_index_type  si = 0;
            src_index_type  sj = 0;
            index_type      di = 0;
            index_type      dj = 0;

            for (;  di < rows();  ++di, ++si)
            {
                for (;  dj < columns();  ++dj, ++sj)
                {
                    (*this)(di, dj) = rhs(si, sj);
                }
            }
        }
    }

    inline constexpr void
    fs_matrix4f_simd_engine::swap(fs_matrix4f_simd_engine& rhs) noexcept
    {
        if (&rhs != this)
        {
            for (index_type i = 0;  i < 4*4;  ++i)
            {
                STD_LA::detail::la_swap(ma_elems[i], rhs.ma_elems[i]);
            }
        }
    }

    inline constexpr void
    fs_matrix4f_simd_engine::swap_columns(index_type j1, index_type j2) noexcept
    {
        if (j1 != j2)
        {
            for (index_type i = 0;  i < 4;  ++i)
            {
                STD_LA::detail::la_swap(ma_elems[i*4 + j1], ma_elems[i*4 + j2]);
            }
        }
    }

    inline constexpr void
    fs_matrix4f_simd_engine::swap_rows(index_type i1, index_type i2) noexcept
    {
        if (i1 != i2)
        {
            for (index_type j = 0;  j < 4;  ++j)
            {
                STD_LA::detail::la_swap(ma_elems[i1*4 + j], ma_elems[i2*4 + j]);
            }
        }
    }

    /// Alias for a fixed size matrix type implemented using simd instructions.
    using matrix4 = STD_LA::matrix<fs_matrix4f_simd_engine>;

} // namespace linear_algebra

#endif //LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
