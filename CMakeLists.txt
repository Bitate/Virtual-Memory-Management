cmake_minimum_required(VERSION 3.8)

set(this Virtual_Memory_Management)

# Visual Studio Code links object files dynamically,
# but googletest links statically, we set this to
# force gooletest to link object files dynamically.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
project(${this} CXX)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(googletest)

