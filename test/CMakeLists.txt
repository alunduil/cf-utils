find_library(CHECK_LIBRARY
  NAMES check
  )

add_subdirectory(test_unit)
add_subdirectory(test_integration)
