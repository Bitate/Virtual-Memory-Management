cmake_minimum_required(VERSION 3.8)

set(this Virtual_Memory_Management)

project(${this} CXX)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(googletest)

