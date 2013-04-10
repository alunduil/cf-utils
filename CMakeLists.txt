cmake_minimum_required(VERSION 2.8)
project(cf-utils C)

set(CF_UTILS_VERSION 9999)

add_subdirectory(lib)
add_subdirectory(src)

add_subdirectory(test EXCLUDE_FROM_ALL)
