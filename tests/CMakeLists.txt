find_package(CHECK 0.9.12 REQUIRED)

if(${CHECK_FOUND})
	add_definitions(${CHECK_DEFINITIONS})
	include_directories(${CHECK_INCLUDE_DIR})

	enable_testing()

	add_subdirectory(units)
endif()
