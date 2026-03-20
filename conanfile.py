from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class TestConan2Conan(ConanFile):
    name = "test_conan2"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "CMakeLists.txt", "main.cpp"

    def requirements(self):
        self.requires("nlohmann_json/3.11.2")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
