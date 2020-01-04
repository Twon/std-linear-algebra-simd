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
        using storage_type    = std::experimental::parallelism_v2::fixed_size_simd<float, 4>;
        using engine_category = STD_LA::mutable_vector_engine_tag;
        using element_type    = typename storage_type::value_type;
        using value_type      = typename storage_type::value_type;
        using reference       = float;
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
        //constexpr fs_vector4f_simd_engine(const storage_type value);
        template<class U>
        constexpr fs_vector4f_simd_engine(std::initializer_list<U> list);

        constexpr fs_vector4f_simd_engine(fs_vector4f_simd_engine&&) noexcept = default;
        constexpr fs_vector4f_simd_engine(fs_vector4f_simd_engine const&) = default;

        constexpr fs_vector4f_simd_engine& operator =(fs_vector4f_simd_engine&&) noexcept = default;
        constexpr fs_vector4f_simd_engine& operator =(fs_vector4f_simd_engine const&) = default;

        /*! For accessing the underlying simd we take a copy of the underlying type
            [simd.subscr] - scalar access
                value_type operator[](size_type) const;
         */
        constexpr const_reference   operator ()(index_type i) const;
        constexpr const_iterator    begin() const noexcept;
        constexpr const_iterator    end() const noexcept;

        constexpr size_type     capacity() const noexcept;
        constexpr index_type    elements() const noexcept;
        constexpr size_type     size() const noexcept;

        constexpr reference     operator ()(index_type i);
        constexpr iterator      begin() noexcept;
        constexpr iterator      end() noexcept;

        //constexpr storage_type  simd() noexcept { return ma_elems; }

        constexpr void  swap(fs_vector4f_simd_engine& rhs) noexcept;
        constexpr void  swap_elements(index_type i, index_type j) noexcept;

    private:

        //alignas(16)
        union {
            float data[4];
            storage_type ma_elems;
        };
    };

    inline constexpr fs_vector4f_simd_engine::fs_vector4f_simd_engine()
    :   ma_elems()
    {
    }

    template<class U>
    inline constexpr fs_vector4f_simd_engine::fs_vector4f_simd_engine(std::initializer_list<U> list)
    :   ma_elems(list.begin(), std::experimental::parallelism_v2::element_aligned)
    {

    }

    inline constexpr typename fs_vector4f_simd_engine::const_reference
    fs_vector4f_simd_engine::operator ()(index_type i) const
    {
        return data[i];
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
        return data[i];
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
                STD_LA::detail::la_swap(data[i], rhs.data[i]);
            }
        }
    }

    inline constexpr void
    fs_vector4f_simd_engine::swap_elements(index_type i, index_type j) noexcept
    {
        STD_LA::detail::la_swap(data[i], data[j]);
    }

    /// Alias for a fixed size vector type implemented using simd instructions.
    using vector4f = STD_LA::vector<fs_vector4f_simd_engine>;

} // namespace linear_algebra

namespace STD_LA {

// Addition - vector

template<>
struct matrix_addition_engine_traits<matrix_operation_traits, linear_algebra::fs_vector4f_simd_engine, linear_algebra::fs_vector4f_simd_engine>
{
	using element_type_1 = float;
	using element_type_2 = float;
	using element_type   = float;
	using engine_type    = linear_algebra::fs_vector4f_simd_engine;
};

template<>
auto matrix_addition_traits<matrix_operation_traits, vector<linear_algebra::fs_vector4f_simd_engine>, vector<linear_algebra::fs_vector4f_simd_engine>>::add
(vector<linear_algebra::fs_vector4f_simd_engine> const& v1, vector<linear_algebra::fs_vector4f_simd_engine> const& v2) -> result_type
{
	PrintOperandTypes<result_type>("vector4f addition_traits", v1, v2);

    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&v1(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type rhs(&v2(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type result = lhs + rhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_subtraction_engine_traits<
           matrix_operation_traits,
           linear_algebra::fs_vector4f_simd_engine,
           linear_algebra::fs_vector4f_simd_engine
       >
{
	using element_type_1 = float;
	using element_type_2 = float;
	using element_type   = float;
	using engine_type    = linear_algebra::fs_vector4f_simd_engine;
};

template<>
auto matrix_subtraction_traits<
         matrix_operation_traits,
         vector<linear_algebra::fs_vector4f_simd_engine>,
         vector<linear_algebra::fs_vector4f_simd_engine>
      >::subtract(
                  vector<linear_algebra::fs_vector4f_simd_engine> const& v1,
                  vector<linear_algebra::fs_vector4f_simd_engine> const& v2
             ) -> result_type
{
	PrintOperandTypes<result_type>("vector4f subtraction_traits", v1, v2);

    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&v1(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type rhs(&v2(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type result = lhs - rhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_negation_engine_traits<matrix_operation_traits, linear_algebra::fs_vector4f_simd_engine>
{
    using element_type = float;
    using engine_type  = linear_algebra::fs_vector4f_simd_engine;
};

template<>
auto
matrix_negation_traits<matrix_operation_traits, vector<linear_algebra::fs_vector4f_simd_engine>>::negate
        (vector<linear_algebra::fs_vector4f_simd_engine> const& v) -> result_type
{
    PrintOperandTypes<result_type>("vector4f negation_traits", v);

    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&v(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type result = -lhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, linear_algebra::fs_vector4f_simd_engine, detail::element_tag<float>>
{
    using element_type = float;
    using engine_type  = linear_algebra::fs_vector4f_simd_engine;
};

template<>
auto
matrix_multiplication_traits<matrix_operation_traits, vector<linear_algebra::fs_vector4f_simd_engine>, float>::multiply
        (vector<linear_algebra::fs_vector4f_simd_engine> const& v, float const& s) -> result_type
{
    PrintOperandTypes<result_type>("vector4f multiplication_traits (v*s)", v, s);

    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&v(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type result = lhs * s;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
struct matrix_multiplication_engine_traits<matrix_operation_traits, detail::element_tag<float>, linear_algebra::fs_vector4f_simd_engine>
{
    using element_type = float;
    using engine_type  = linear_algebra::fs_vector4f_simd_engine;
};

template<>
auto
matrix_multiplication_traits<matrix_operation_traits, float, vector<linear_algebra::fs_vector4f_simd_engine>>::multiply
        (float const& s, vector<linear_algebra::fs_vector4f_simd_engine> const& v) -> result_type
{
    PrintOperandTypes<result_type>("vector4f multiplication_traits (s*v)", s, v);

    linear_algebra::fs_vector4f_simd_engine::storage_type rhs(&v(0), std::experimental::parallelism_v2::vector_aligned);
    linear_algebra::fs_vector4f_simd_engine::storage_type result = s * rhs;
    initializer_list<float> initialiser = {0.0f, 0.0f, 0.0f, 0.0f};
    result.copy_to(const_cast<float*>(initialiser.begin()), std::experimental::parallelism_v2::element_aligned);
    return result_type(initialiser);
}

template<>
auto
matrix_multiplication_traits<
    matrix_operation_traits,
    vector<linear_algebra::fs_vector4f_simd_engine>,
    vector<linear_algebra::fs_vector4f_simd_engine>
>::multiply(
            vector<linear_algebra::fs_vector4f_simd_engine> const& v1,
            vector<linear_algebra::fs_vector4f_simd_engine> const& v2
        ) -> result_type
{
    PrintOperandTypes<result_type>("vector4f multiplication_traits (v*v)", v1, v2);

//    linear_algebra::fs_vector4f_simd_engine::storage_type lhs(&v1(0), std::experimental::parallelism_v2::vector_aligned);
//    linear_algebra::fs_vector4f_simd_engine::storage_type rhs(&v2(0), std::experimental::parallelism_v2::vector_aligned);
//    result_type result = lhs * rhs;
//    return result;
    return result_type();
}

}

#endif //LINEAR_ALGEBRA_SIMD_VECTOR_SIMD_HPP
