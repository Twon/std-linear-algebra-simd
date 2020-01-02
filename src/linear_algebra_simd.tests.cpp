#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <linear_algebra_simd.hpp>

using namespace linear_algebra;

/*! Helper function to capture constexpr results in catch test reporting.
    \note
        Credit to Jason Turner: https://twitter.com/lefticus/status/980530307580514304
    \tparam B
        Compile time condition.
    \return
        The compile time condition result.
 */
template<bool B>
constexpr bool static_test()
{
    static_assert(B);
    return B;
}


TEST_CASE("Test ABI type traits", "[simd.abi.traits]")
{
//    REQUIRE(static_test<sizeof(vector4) == 4 * sizeof(float)>());
//    REQUIRE(static_test<is_abi_tag<simd_abi::detail::sse_register>::type::value>());
//    REQUIRE(static_test<is_abi_tag<simd_abi::detail::avx_register>::type::value>());
//    REQUIRE(static_test<is_abi_tag<simd_abi::detail::avx512_register>::type::value>());
}

TEST_CASE("Test SIMD vector operations", "[linear_algebra.vector.simd.operators]")
{

    GIVEN("A pair of vectors")
    {
        vector4 a = {1.0f, 2.0f, 3.0f, 4.0f};
        vector4 b = {2.0f, 4.0f, 6.0f, 8.0f};

        WHEN("Performing addition of vectors")
        {
            vector4 result = a + b;
            vector4 expected = {3.0f, 6.0f, 9.0f, 12.0f};
            REQUIRE(result == expected);
        }
    }

}

TEST_CASE("Test matrix operators", "[linear_algebra.matrix4.operators]")
{
    GIVEN("Multiple matrices")
    {
/*        matrix4 a{1.0, 0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0, 0.0,
                  0.0, 0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0, 1.0};
*/
    }
//    REQUIRE(static_test<is_abi_tag<simd_abi::scalar>::type::value>());
//    REQUIRE(static_test<is_abi_tag<simd_abi::detail::sse_register>::type::value>());
//    REQUIRE(static_test<is_abi_tag<simd_abi::detail::avx_register>::type::value>());
//    REQUIRE(static_test<is_abi_tag<simd_abi::detail::avx512_register>::type::value>());
}
