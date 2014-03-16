cmake_minimum_required(VERSION 2.8)
project(cfutils C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

set(CFUTILS_MAJOR_VERSION 0)
set(CFUTILS_MINOR_VERSION 0)
set(CFUTILS_PATCH_VERSION 0)

set(CFUTILS_VERSION "${CFUTILS_MAJOR_VERSION}.${CFUTILS_MINOR_VERSION}.${CFUTILS_PATCH_VERSION}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Werror -pedantic")

set(BUILD_SHARED_LIBS "YES")

add_subdirectory(lib)

enable_testing()
add_subdirectory(tests EXCLUDE_FROM_ALL)
