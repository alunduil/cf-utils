# ============================================================================ #
# Find the check library and define helpful variables.                         #
# ============================================================================ #
#
# This has been adapted (slightly) from the following:
# https://github.com/swift-nav/libswiftnav/blob/master/cmake/FindCheck.cmake
#
# This module defines the following variables:
# CHECK_INCLUDE_DIRS — where to find check.h and check_stdint.h
# CHECK_LIBRARIES    — the libraries to link against to use check
# CHECK_FOUND        — TRUE if found; otherwise, check should not be used
#
# This module defines the following macros:
# CHECK_ADD_TEST     — compile and link and add test given test name.
#

include(FindPkgConfig)

if(${CHECK_FIND_REQUIRED})
	set(_pkgconfig_REQUIRED "REQUIRED")
else()
	set(_pkgconfig_REQUIRED "")
endif()

if(${CHECK_MIN_VERSION})
	pkg_search_module(CHECK ${_pkgconfig_REQUIRED} check>=${CHECK_MIN_VERSION})
else()
	pkg_search_module(CHECK ${_pkgconfig_REQUIRED} check)
endif()

if(NOT ${CHECK_FOUND} AND NOT ${PKG_CONFIG_FOUND})
	find_path(CHECK_INCLUDE_DIRS
		NAMES check.h check_stdint.h
	)

	find_library(CHECK_LIBRARIES check)

	if(${CHECK_INCLUDE_DIRS} AND ${CHECK_LIBRARIES})
		set(CHECK_FOUND "YES")
	else()
		if(${CHECK_FIND_REQUIRED})
			message(FATAL_ERROR "Check Not Found!")
		endif()
	endif()
endif()

mark_as_advanced(CHECK_INCLUDE_DIRS CHECK_LIBRARIES)

macro(check_add_test CHECK_NAME)
	add_executable(${CHECK_NAME} ${CHECK_NAME}.c)
	target_link_libraries(${CHECK_NAME} ${CHECK_LIBRARIES})

	add_test(${CHECK_NAME} ${EXECUTABLE_OUTPUT_PATH}/${CHECK_NAME})
endmacro()