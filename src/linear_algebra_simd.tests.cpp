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


TEST_CASE("Test SIMD vector operations", "[linear_algebra.vector.simd.operators]")
{
    GIVEN("A pair of vectors")
    {
        vector4f a = {1.0f, 2.0f, 3.0f, 4.0f};
        vector4f b = {2.0f, 4.0f, 6.0f, 8.0f};
        const float scalar = 2.0;

        WHEN("Performing addition of vectors")
        {
            vector4f result = a + b;
            THEN("Expect element wise addition of values")
            {
                vector4f expected = {3.0f, 6.0f, 9.0f, 12.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing subtraction of vectors")
        {
            vector4f result = b - a;
            THEN("Expect element wise subtraction of values")
            {
                vector4f expected = {1.0f, 2.0f, 3.0f, 4.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing negation of vectors")
        {
            vector4f result = -a;
            THEN("Expect element wise negation of values")
            {
                vector4f expected = {-1.0f, -2.0f, -3.0f, -4.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a vector and a scalar")
        {
            vector4f result = a * scalar;
            THEN("Expect element wise scaling of values")
            {
                vector4f expected = {2.0f, 4.0f, 6.0f, 8.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a scalar and a vector")
        {
            vector4f result = scalar * a;
            THEN("Expect element wise scaling of values")
            {
                vector4f expected = {2.0f, 4.0f, 6.0f, 8.0f};
                REQUIRE(result == expected);
            }
        }
    }
}

TEST_CASE("Test matrix operators", "[linear_algebra.matrix4.operators]")
{
    GIVEN("A pair of matrices")
    {
        matrix4x4f a{   1.0f, 2.0f, 3.0f, 4.0f,
                        5.0f, 6.0f, 7.0f, 8.0f,
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f};
        matrix4x4f b{   2.0f, 4.0f, 6.0f, 8.0f,
                        10.0f, 12.0f, 14.0f, 16.0f,
                        18.0f, 20.0f, 22.0f, 24.0f,
                        26.0f, 28.0f, 30.0f, 32.0f};
        const float scalar = 2.0;

        WHEN("Performing addition of matrices")
        {
            matrix4x4f result = a + b;
            THEN("Expect element wise addition of values")
            {
                matrix4x4f expected = {   3.0f, 6.0f, 9.0f, 12.0f,
                                          15.0f, 18.0f, 21.0f, 24.0f,
                                          27.0f, 30.0f, 33.0f, 36.0f,
                                          39.0f, 42.0f, 45.0f, 48.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing subtraction of matrices")
        {
            matrix4x4f result = b - a;
            THEN("Expect element wise subtraction of values")
            {
                matrix4x4f expected = {   1.0f, 2.0f, 3.0f, 4.0f,
                                          5.0f, 6.0f, 7.0f, 8.0f,
                                          9.0f, 10.0f, 11.0f, 12.0f,
                                          13.0f, 14.0f, 15.0f, 16.0f };
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing negation of a matrix")
        {
            matrix4x4f result = -a;
            THEN("Expect element wise negation of values")
            {
                matrix4x4f expected = {   -1.0f, -2.0f, -3.0f, -4.0f,
                                          -5.0f, -6.0f, -7.0f, -8.0f,
                                          -9.0f, -10.0f, -11.0f, -12.0f,
                                          -13.0f, -14.0f, -15.0f, -16.0f };
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a matrix and a scalar")
        {
            matrix4x4f result = a * scalar;
            THEN("Expect element wise scaling of values")
            {
                matrix4x4f expected = {   2.0f, 4.0f, 6.0f, 8.0f,
                                          10.0f, 12.0f, 14.0f, 16.0f,
                                          18.0f, 20.0f, 22.0f, 24.0f,
                                          26.0f, 28.0f, 30.0f, 32.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a scalar and a matrix")
        {
            matrix4x4f result = scalar * a;
            THEN("Expect element wise scaling of values")
            {
                matrix4x4f expected = {   2.0f, 4.0f, 6.0f, 8.0f,
                                          10.0f, 12.0f, 14.0f, 16.0f,
                                          18.0f, 20.0f, 22.0f, 24.0f,
                                          26.0f, 28.0f, 30.0f, 32.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a matrix and a vector")
        {
            vector4f v = { 0.0f, 0.0f, 0.0f, 1.0f};
            matrix4x4f m {  1.0f, 0.0f, 0.0f, 10.0f,
                            0.0f, 1.0f, 0.0f, 10.0f,
                            0.0f, 0.0f, 1.0f, 10.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};
            vector4f result = m * v;
            THEN("Expect translated position of a homogeneous vector")
            {
                vector4f expected = {10.0f, 10.0f, 10.0f, 1.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a vector and a matrix")
        {
            vector4f v = { 0.0f, 0.0f, 0.0f, 1.0f};
            matrix4x4f m {  1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            10.0f, 10.0f, 10.0f, 1.0f};
            vector4f result = v * m;
            THEN("Expect translated position of a homogeneous vector")
            {
                vector4f expected = {10.0f, 10.0f, 10.0f, 1.0f};
                REQUIRE(result == expected);
            }
        }
        WHEN("Performing multiplication of a matrix and a matrix")
        {
            matrix4x4f m1 { 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            10.0f, 10.0f, 10.0f, 1.0f};
            matrix4x4f m2 { 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};
            matrix4x4f result = m1 * m2;
            THEN("Expect element wise negation of values")
            {
                matrix4x4f expected = { 1.0f, 0.0f, 0.0f, 0.0f,
                                        0.0f, 1.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f, 1.0f, 0.0f,
                                        10.0f, 10.0f, 10.0f, 1.0f};
                REQUIRE(result == expected);
            }
        }
    }
}
