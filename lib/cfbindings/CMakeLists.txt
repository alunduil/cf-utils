set(CFBINDINGS_HEADERS ${CFBINDINGS_HEADERS} account.h)
set(CFBINDINGS_SOURCES ${CFBINDINGS_SOURCES} account.c)

set(CFBINDINGS_HEADERS ${CFBINDINGS_HEADERS} container.h)
set(CFBINDINGS_SOURCES ${CFBINDINGS_SOURCES} container.c)

add_library(cfbindings ${CFBINDINGS_HEADERS} ${CFBINDINGS_SOURCES})
set_target_properties(cfbindings PROPERTIES VERSION ${CFUTILS_VERSION} SOVERSION 1)

install(FILES ${CFBINDINGS_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME})
install(TARGETS cfbindings DESTINATION lib EXPORT cfbindings-targets)
install(EXPORT cfbindings-targets DESTINATION share/${CMAKE_PROJECT_NAME}-${CFUTILS_VERSION}}/cmake)

export(TARGETS cfbindings FILE cfbindings-targets.cmake)

configure_file(
	${CMAKE_SOURCE_DIR}/pkg/cfbindings-config.cmake.in
	${CMAKE_BINARY_DIR}/pkg/cfbindings-config.cmake
	@ONLY
)
configure_file(
	${CMAKE_SOURCE_DIR}/pkg/cfbindings-config-version.cmake.in
	${CMAKE_BINARY_DIR}/pkg/cfbindings-config-version.cmake
	@ONLY
)

install(FILES
	${CMAKE_BINARY_DIR}/pkg/cfbindings-config.cmake
	${CMAKE_BINARY_DIR}/pkg/cfbindings-config-version.cmake
	DESTINATION lib/cfbindings-${CFUTILS_VERSION}
)
