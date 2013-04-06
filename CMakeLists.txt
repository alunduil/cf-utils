project(cf-utils C)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_subdirectory(lib)
add_subdirectory(src)

add_subdirectory(test EXCLUDE_FROM_ALL)

add_subdirectory(cmake)
