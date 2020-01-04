#ifndef LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
#define LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP

#pragma once

#include <experimental/simd>
#include <vector_simd.hpp>

namespace linear_algebra {

    /*! \class fs_matrix4f_simd_engine
        Fixed size martix for 4 by 4 martrices using SIMD instructions to parallise computations
     */
    class fs_matrix4f_simd_engine
    {
    public:
        using storage_type    = std::experimental::parallelism_v2::fixed_size_simd<float, 16>;
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
        // alignas(16) float
        union {
            float data[16];
            storage_type ma_elems;
        };
    };


    inline constexpr fs_matrix4f_simd_engine::fs_matrix4f_simd_engine()
    :   ma_elems()
    {
    }

    template<class U> inline
    constexpr
    fs_matrix4f_simd_engine::fs_matrix4f_simd_engine(std::initializer_list<U> list)
    :   ma_elems(list.begin(), std::experimental::parallelism_v2::element_aligned)
    {
    }

    inline constexpr typename fs_matrix4f_simd_engine::const_reference
    fs_matrix4f_simd_engine::operator ()(index_type i, index_type j) const
    {
        return data[i*4 + j];
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
        return data[i*4 + j];
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
                STD_LA::detail::la_swap(data[i], rhs.data[i]);
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
                STD_LA::detail::la_swap(data[i*4 + j1], data[i*4 + j2]);
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
                STD_LA::detail::la_swap(data[i1*4 + j], data[i2*4 + j]);
            }
        }
    }

    /// Alias for a fixed size matrix type implemented using simd instructions.
    using matrix4x4f = STD_LA::matrix<fs_matrix4f_simd_engine>;

} // namespace linear_algebra

namespace STD_LA
{

template<>
struct matrix_addition_engine_traits<matrix_operation_traits, linear_algebra::fs_matrix4f_simd_engine, linear_algebra::fs_matrix4f_simd_engine>
{
	using element_type_1 = float;
	using element_type_2 = float;
	using element_type   = float;
	using engine_type    = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto matrix_addition_traits<
        matrix_operation_traits,
        matrix<linear_algebra::fs_matrix4f_simd_engine>,
        matrix<linear_algebra::fs_matrix4f_simd_engine>
    >::add(
            matrix<linear_algebra::fs_matrix4f_simd_engine> const& m1,
            matrix<linear_algebra::fs_matrix4f_simd_engine> const& m2
        ) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f addition_traits", m1, m2);

    linear_algebra::fs_matrix4f_simd_engine::storage_type lhs(&m1(0,0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_matrix4f_simd_engine::storage_type rhs(&m2(0,0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_matrix4f_simd_engine::storage_type result = lhs + rhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_subtraction_engine_traits<matrix_operation_traits, linear_algebra::fs_matrix4f_simd_engine, linear_algebra::fs_matrix4f_simd_engine>
{
	using element_type_1 = float;
	using element_type_2 = float;
	using element_type   = float;
	using engine_type    = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto matrix_subtraction_traits<
        matrix_operation_traits,
        matrix<linear_algebra::fs_matrix4f_simd_engine>,
        matrix<linear_algebra::fs_matrix4f_simd_engine>
    >::subtract(
            matrix<linear_algebra::fs_matrix4f_simd_engine> const& m1,
            matrix<linear_algebra::fs_matrix4f_simd_engine> const& m2
        ) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f subtraction_traits", m1, m2);

    linear_algebra::fs_matrix4f_simd_engine::storage_type lhs(&m1(0,0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_matrix4f_simd_engine::storage_type rhs(&m2(0,0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_matrix4f_simd_engine::storage_type result = lhs - rhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_negation_engine_traits<matrix_operation_traits, linear_algebra::fs_matrix4f_simd_engine>
{
	using element_type = float;
	using engine_type  = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto
matrix_negation_traits<matrix_operation_traits, matrix<linear_algebra::fs_matrix4f_simd_engine>>::negate
(matrix<linear_algebra::fs_matrix4f_simd_engine> const& m) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f negation_traits", m);

    linear_algebra::fs_matrix4f_simd_engine::storage_type lhs(&m(0,0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_matrix4f_simd_engine::storage_type result = -lhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, linear_algebra::fs_matrix4f_simd_engine, detail::element_tag<float>>
{
	using element_type = float;
	using engine_type  = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto
matrix_multiplication_traits<matrix_operation_traits, matrix<linear_algebra::fs_matrix4f_simd_engine>, float>::multiply
(matrix<linear_algebra::fs_matrix4f_simd_engine> const& m, float const& s) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f multiplication_traits (m*s)", m, s);

    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&m(0, 0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type result = lhs * s;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, detail::element_tag<float>, linear_algebra::fs_matrix4f_simd_engine>
{
	using element_type = float;
	using engine_type  = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto
matrix_multiplication_traits<matrix_operation_traits, float, matrix<linear_algebra::fs_matrix4f_simd_engine>>::multiply
(float const& s, matrix<linear_algebra::fs_matrix4f_simd_engine> const& m) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f multiplication_traits (s*m)", s, m);

    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&m(0, 0), std::experimental::parallelism_v2::vector_aligned);
    // Appears to be adding the results not multiplying???
    linear_algebra::fs_vector4f_simd_engine::storage_type result = lhs * s;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}
/*
template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, linear_algebra::fs_vector4f_simd_engine, linear_algebra::fs_matrix4f_simd_engine>
{
	using element_type = float;
	using engine_type  = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto
matrix_multiplication_traits<matrix_operation_traits, vector<linear_algebra::fs_vector4f_simd_engine>, matrix<linear_algebra::fs_matrix4f_simd_engine>>::multiply
(vector<linear_algebra::fs_vector4f_simd_engine> const& v, matrix<linear_algebra::fs_matrix4f_simd_engine> const& m) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f multiplication_traits (v*m)", v, m);

	return result_type{ (v(0) * m(0, 0)) + (v(1) * m(1, 0)) + (v(2) * m(2, 0)) + (v(3) * m(3, 0)),
						(v(0) * m(0, 1)) + (v(1) * m(1, 1)) + (v(2) * m(2, 1)) + (v(3) * m(3, 1)),
						(v(0) * m(0, 2)) + (v(1) * m(1, 2)) + (v(2) * m(2, 2)) + (v(3) * m(3, 2)),
						(v(0) * m(0, 3)) + (v(1) * m(1, 3)) + (v(2) * m(2, 3)) + (v(3) * m(3, 3)) };
}

template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, linear_algebra::fs_matrix4f_simd_engine, linear_algebra::fs_vector4f_simd_engine>
{
	using element_type = float;
	using engine_type  = linear_algebra::fs_vector4f_simd_engine;
};

template<>
auto
matrix_multiplication_traits<matrix_operation_traits, matrix<linear_algebra::fs_matrix4f_simd_engine>, vector<linear_algebra::fs_vector4f_simd_engine>>::multiply
(matrix<linear_algebra::fs_matrix4f_simd_engine> const& m, vector<linear_algebra::fs_vector4f_simd_engine> const& v) -> result_type
{
	PrintOperandTypes<result_type>("matrix4x4f multiplication_traits (m*v)", m, v);

	return result_type{ (m(0, 0) * v(0)) + (m(0, 1) * v(1)) + (m(0, 2) * v(2)) + (m(0, 3) * v(3)),
						(m(1, 0) * v(0)) + (m(1, 1) * v(1)) + (m(1, 2) * v(2)) + (m(1, 3) * v(3)),
						(m(2, 0) * v(0)) + (m(2, 1) * v(1)) + (m(2, 2) * v(2)) + (m(2, 3) * v(3)),
						(m(3, 0) * v(0)) + (m(3, 1) * v(1)) + (m(3, 2) * v(2)) + (m(3, 3) * v(3)) };
}


template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, linear_algebra::fs_matrix4f_simd_engine, linear_algebra::fs_matrix4f_simd_engine>
{
	using element_type = float;
	using engine_type  = linear_algebra::fs_matrix4f_simd_engine;
};

template<>
auto matrix_multiplication_traits<matrix_operation_traits, matrix<linear_algebra::fs_matrix4f_simd_engine>, matrix<linear_algebra::fs_matrix4f_simd_engine>>::multiply
(matrix<linear_algebra::fs_matrix4f_simd_engine> const& m1, matrix<linear_algebra::fs_matrix4f_simd_engine> const& m2) -> result_type
{
	PrintOperandTypes<result_type>("float22 multiplication_traits (m*m)", m1, m2);

	return result_type{ (m1(0, 0) * m2(0, 0)) + (m1(0, 1) * m2(1, 0)) + (m1(0, 2) * m2(2, 0)) + (m1(0, 3) * m2(3, 0)), (m1(0, 0) * m2(0, 1)) + (m1(0, 1) * m2(1, 1)) + (m1(0, 2) * m2(2, 1)) + (m1(0, 3) * m2(3, 1)), (m1(0, 0) * m2(0, 2)) + (m1(0, 1) * m2(1, 2)) + (m1(0, 2) * m2(2, 2)) + (m1(0, 3) * m2(3, 2)), (m1(0, 0) * m2(0, 3)) + (m1(0, 1) * m2(1, 3)) + (m1(0, 2) * m2(2, 3)) + (m1(0, 3) * m2(3, 3)),
						(m1(1, 0) * m2(0, 0)) + (m1(1, 1) * m2(1, 0)) + (m1(1, 2) * m2(2, 0)) + (m1(1, 3) * m2(3, 0)), (m1(1, 0) * m2(0, 1)) + (m1(1, 1) * m2(1, 1)) + (m1(1, 2) * m2(2, 1)) + (m1(1, 3) * m2(3, 1)), (m1(1, 0) * m2(0, 2)) + (m1(1, 1) * m2(1, 2)) + (m1(1, 2) * m2(2, 2)) + (m1(1, 3) * m2(3, 2)), (m1(1, 0) * m2(0, 3)) + (m1(1, 1) * m2(1, 3)) + (m1(1, 2) * m2(2, 3)) + (m1(1, 3) * m2(3, 3)),
						(m1(2, 0) * m2(0, 0)) + (m1(2, 1) * m2(1, 0)) + (m1(2, 2) * m2(2, 0)) + (m1(2, 3) * m2(3, 0)), (m1(2, 0) * m2(0, 1)) + (m1(2, 1) * m2(1, 1)) + (m1(2, 2) * m2(2, 1)) + (m1(2, 3) * m2(3, 1)), (m1(2, 0) * m2(0, 2)) + (m1(2, 1) * m2(1, 2)) + (m1(2, 2) * m2(2, 2)) + (m1(2, 3) * m2(3, 2)), (m1(2, 0) * m2(0, 3)) + (m1(2, 1) * m2(1, 3)) + (m1(2, 2) * m2(2, 3)) + (m1(2, 3) * m2(3, 3)),
						(m1(3, 0) * m2(0, 0)) + (m1(3, 1) * m2(1, 0)) + (m1(3, 2) * m2(2, 0)) + (m1(3, 3) * m2(3, 0)), (m1(3, 0) * m2(0, 1)) + (m1(3, 1) * m2(1, 1)) + (m1(3, 2) * m2(2, 1)) + (m1(3, 3) * m2(3, 1)), (m1(3, 0) * m2(0, 2)) + (m1(3, 1) * m2(1, 2)) + (m1(3, 2) * m2(2, 2)) + (m1(3, 3) * m2(3, 2)), (m1(3, 0) * m2(0, 3)) + (m1(3, 1) * m2(1, 3)) + (m1(3, 2) * m2(2, 3)) + (m1(3, 3) * m2(3, 3)) };
}
*/
} // namespace STD_LA


#endif //LINEAR_ALGEBRA_SIMD_MATRIX_SIMD_HPP
