include(FindCHECK)

if(${CHECK_FOUND})
	add_definitions(${CHECK_DEFINITIONS})

	include_directories(${CHECK_INCLUDE_DIR})

	macro(add_target_with_test CHECK_NAME)
		add_executable(${CHECK_NAME} ${CHECK_NAME}.c)
		target_link_libraries(${CHECK_NAME} ${CHECK_LIBRARIES})

		add_test(${CHECK_NAME} ${EXECUTABLE_OUTPUT_PATH}/${CHECK_NAME})
	endmacro()

	add_subdirectory(units)
else()
	message("check not found")
endif()
