project(test_package LANGUAGES CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(linear_algebra_simd REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(test_linear_algebra_simd ../../src/linear_algebra_simd.tests.cpp)
target_link_libraries(test_linear_algebra_simd PRIVATE linear_algebra_simd::linear_algebra_simd Catch2::Catch2)

target_compile_options(test_linear_algebra_simd
    PRIVATE
        #$<$<BOOL:${MINGW}>:-Wa,-mbig-obj>
)

enable_testing()
include(Catch)
catch_discover_tests(test_linear_algebra_simd)