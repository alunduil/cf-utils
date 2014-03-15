#
# Find the check library and define helpful variables.
#

# This module defines the following variables:
# CHECK_INCLUDE_DIR — where to find check.h and check_stdint.h
# CHECK_LIBRARIES   — the libraries to link against to use check
# CHECK_DEFINITIONS — definitions to be added before compiling code (call
#                     add_definitions(${CHECK_DEFINITIONS}))
# CHECK_FOUND       — TRUE if found; otherwise, check should not be used

find_path(CHECK_CHECK_INCLUDE_DIR NAMES check.h check_stdint.h)

find_library(CHECK_LIBRARY check)

if (CHECK_LIBRARY AND CHECK_CHECK_INCLUDE_DIR)
	set(CHECK_INCLUDE_DIR ${CHECK_CHECK_INCLUDE_DIR})
	set(CHECK_LIBRARIES ${CHECK_LIBRARY})
	set(CHECK_FOUND "YES")
endif()
