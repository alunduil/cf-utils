cmake_minimum_required(VERSION 2.8)
project(cf-utils C)

set(CF_UTILS_VERSION 9999)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Werror -pedantic")

set(BUILD_SHARED_LIBS True)

if(${CMAKE_BUILD_TYPE} EQUAL "Debug")
	set(CMAKE_VERBOSE_MAKEFILE True)
endif()

add_subdirectory(lib)
#add_subdirectory(src)

enable_testing()
add_subdirectory(test EXCLUDE_FROM_ALL)
