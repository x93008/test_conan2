cmake_minimum_required(VERSION 3.15)
project(test_conan2 CXX)

find_package(libzip REQUIRED CONFIG)

message("ZLIB_FOUND: ${ZLIB_FOUND}")

add_executable(main main.cpp)
target_link_libraries(main PRIVATE libzip::zip)
