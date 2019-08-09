cmake_minimum_required(VERSION 3.10)

project(cppmarkov)

set(FILES src/main.cpp src/Markov.cpp src/Markov.hpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(tests)

add_executable(cppmarkov ${FILES})

