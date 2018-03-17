cmake_minimum_required(VERSION 3.7)
project(cpp_memory)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/pointer.hpp src/ptr/shared_ptr.hpp src/ptr/ptr.hpp)
add_executable(cpp_memory ${SOURCE_FILES})
