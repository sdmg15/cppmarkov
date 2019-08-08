cmake_minimum_required(VERSION 3.10)

project(cppmarkov)

set(FILES src/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(tests)

add_executable(cppmarkov ${FILES})

