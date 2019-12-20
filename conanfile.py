#!/usr/bin/env python
# -*- coding: utf-8 -*-
from conans import ConanFile, CMake

class LinearAlgebraSimdConan(ConanFile):
    name = "linear_algebra_simd"
    version = "0.0.1"
    license = "MIT"
    url = "https://github.com/Twon/std-linear-algebra-simd"
    description = "An linear algebra library implemented using standard library simd data types"
    topics = ("conan", "linear algebra", "header-only", "std", "experimental", "simd")
    exports_sources = "*.txt", "*.h", "*.natvis", "*.cpp", "*.cmake", "*.cmake.in", "LICENSE.txt"
    generators = "cmake"
    requires = "Catch2/2.10.2@catchorg/stable"

    _cmake = None
    @property
    def cmake(self):
        if self._cmake is None:
            self._cmake = CMake(self)
            self._cmake.definitions.update({
                "BUILD_TESTING": False,
                "ENABLE_BUILD_DOCUMENTATION": True
            })
            self._cmake.configure()
        return self._cmake

    def build(self):
        self.cmake.build()
        if self._cmake.definitions["BUILD_TESTING"]:
            self.cmake.test()

    def package(self):
        self.cmake.install()