cmake_minimum_required(VERSION 2.8)
project(cf-utils C)

add_subdirectory(lib)
add_subdirectory(src)

add_subdirectory(test EXCLUDE_FROM_ALL)
add_subdirectory(cmake EXCLUDE_FROM_ALL)

