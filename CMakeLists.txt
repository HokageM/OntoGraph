cmake_minimum_required(VERSION 3.22)
project(OntoTraverse VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(ontographcpp)  

add_subdirectory(src)

add_subdirectory(app)

#enable_testing()
#add_subdirectory(tests)
