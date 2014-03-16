find_package(CHECK)

add_custom_target(tests)

if(${CHECK_FOUND})
	add_definitions(${CHECK_DEFINITIONS})
	include_directories(${CHECK_INCLUDE_DIR})

	macro(check_add_test NAME)
		add_executable(${NAME} ${NAME}.c)
		target_link_libraries(${NAME} ${CHECK_LIBRARIES})

		add_test(${NAME} ${EXECUTABLE_OUTPUT_PATH}/${NAME})
	endmacro()

	add_subdirectory(units)
endif()
