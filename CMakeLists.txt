cmake_minimum_required(VERSION 2.8)
project(cf-utils C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CF_UTILS_VERSION 9999)
string(REGEX REPLACE "[.][^.]*$" "" CF_LIB_VERSION ${CF_UTILS_VERSION})

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Werror -pedantic")

set(BUILD_SHARED_LIBS "YES")

if(${CMAKE_BUILD_TYPE} EQUAL "Debug")
	set(CMAKE_VERBOSE_MAKEFILE True)
endif()

add_subdirectory(lib)

enable_testing()
add_subdirectory(check EXCLUDE_FROM_ALL)
