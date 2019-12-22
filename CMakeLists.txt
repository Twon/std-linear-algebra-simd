cmake_minimum_required(VERSION 3.15.3)

if(NOT DEFINED PROJECT_NAME)
    set(LINEAR_ALGEBRA_SIMD_IS_NOT_SUBPROJECT ON)
endif()

file(STRINGS "version.txt" LINEAR_ALGEBRA_SIMD_VERSION)

project(linear_algebra_simd
    VERSION ${LINEAR_ALGEBRA_SIMD_VERSION}
    DESCRIPTION "A 3D oriented linear algebra library implemented on top of the proposed std::experimental::simd data type"
    LANGUAGES CXX
)

# Include necessary submodules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# CMake includes
include(CTest)
include(FetchContent)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(WriteCompilerDetectionHeader)

set(LINEAR_ALGEBRA_SIMD_PREDEFINED_TARGETS "_BuildTargets")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER ${LINEAR_ALGEBRA_SIMD_PREDEFINED_TARGETS})

# Project includes
include(Documentation)

# Ensure code coverage is switched off for Mac OS until the code coverage library addresses the AppleClang issue
cmake_dependent_option(ENABLE_CODE_COVERAGE "Enable code coverage" ON "\"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"Clang\" OR \"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"GNU\"" OFF)


add_library(linear_algebra_simd INTERFACE)
target_include_directories(linear_algebra_simd
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(linear_algebra_simd
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/linear_algebra_simd.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/matrix_simd.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/quaternion_simd.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/vector_simd.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/linear_algebra_simd.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/matrix_simd.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/quaternion_simd.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/vector_simd.hpp>
)

target_compile_features(linear_algebra_simd
    INTERFACE
        cxx_std_17
)

# namespaced alias for users depending on std_linear_algebra_simd as a sub-project.
add_library(linear_algebra_simd::linear_algebra_simd ALIAS linear_algebra_simd)

write_compiler_detection_header(
    FILE linear_algebra_simd_compiler_detection.hpp
    PREFIX LINEAR_ALGEBRA_SIMD
    COMPILERS GNU Clang MSVC Intel AppleClang
    FEATURES cxx_constexpr
)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
#generate_export_header(linear_algebra_simd)

if(LINEAR_ALGEBRA_SIMD_IS_NOT_SUBPROJECT)

    if (${BUILD_TESTING})
        FetchContent_Declare(
            catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        )

        FetchContent_GetProperties(catch2)
        if(NOT catch2_POPULATED)
            FetchContent_Populate(catch2)
            add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
        endif()

        add_executable(test_linear_algebra_simd "")
        target_sources(test_linear_algebra_simd
            PRIVATE
                src/linear_algebra_simd.tests.cpp
        )

        target_link_libraries(test_linear_algebra_simd
            PRIVATE
                linear_algebra_simd::linear_algebra_simd
                Catch2::Catch2
        )

        target_compile_options(test_linear_algebra_simd
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/W4>
                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Werror;-Wall>
        )

        set_target_properties(test_linear_algebra_simd PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
        )

        enable_testing()
        add_test(
            NAME test_linear_algebra_simd
            COMMAND test_linear_algebra_simd
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )

        list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
        include(Catch)
        catch_discover_tests(test_linear_algebra_simd)
    endif(${BUILD_TESTING})

    if (ENABLE_CODE_COVERAGE)
        FetchContent_Declare(
            codecoverage
            GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov.git
        )

        FetchContent_GetProperties(codecoverage)
        if(NOT codecoverage_POPULATED)
            FetchContent_Populate(codecoverage)
            list(APPEND CMAKE_MODULE_PATH ${codecoverage_SOURCE_DIR}/cmake)
        endif()

        set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
        find_package(codecov)
        add_coverage(test_linear_algebra_simd)
        list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'")
        coverage_evaluate()
    endif()

# Hierarchically copy headers to the install dir
install (
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN
        "*.hpp"
)

install(
    FILES
#        "${CMAKE_CURRENT_SOURCE_DIR}/linear_algebra_simd_export.hpp
        "${CMAKE_CURRENT_SOURCE_DIR}/linear_algebra_simd_compiler_detection.hpp"
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS linear_algebra_simd
        EXPORT linear_algebra_simd-target
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT linear_algebra_simd-target
    NAMESPACE linear_algebra_simd::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/linear_algebra_simd"
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/linear_algebra_simd-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/linear_algebra_simd-config.cmake
    INSTALL_DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/linear_algebra_simd"
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/linear_algebra_simd-version.cmake
    VERSION ${PROPAGATE_CONST_VERSION}
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/linear_algebra_simd-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/linear_algebra_simd-version.cmake
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/linear_algebra_simd"
)

endif(LINEAR_ALGEBRA_SIMD_IS_NOT_SUBPROJECT)