set(CF_BINDINGS_HEADERS ${CF_BINDINGS_HEADERS} account.h)
set(CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} account.c)

set(CF_BINDINGS_HEADERS ${CF_BINDINGS_HEADERS} container.h)
set(CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} container.c)

add_library(cf-bindings ${CF_BINDINGS_HEADERS} ${CF_BINDINGS_SOURCES})
set_target_properties(cf-bindings PROPERTIES VERSION ${CF_LIB_VERSION} SOVERSION 1)

install(FILES ${CF_BINDINGS_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME})
install(TARGETS cf-bindings DESTINATION lib EXPORT cf-bindings-targets)
install(EXPORT cf-bindings-targets DESTINATION share/${CMAKE_PROJECT_NAME}-${CF_UTILS_VERSION}}/cmake)

export(TARGETS cf-bindings FILE cf-bindings-targets.cmake)
