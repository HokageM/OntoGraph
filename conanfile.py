from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain

class OntoGraphConan(ConanFile):
    name = "ontograph"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "app/*", "tests/*"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("tinyxml2/11.0.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.27.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        cmake = CMake(self)
        cmake.install()
    
    def package_info(self):
        self.cpp_info.libs = ["ontograph"]

