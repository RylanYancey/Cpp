cmake_minimum_required(VERSION 3.10)

project(BinaryTreePeople)

add_subdirectory(header)
add_subdirectory(source)

add_executable(main source/main.cpp)