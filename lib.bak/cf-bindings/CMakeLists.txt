set (CF_BINDINGS_HEADERS ${CF_BINDINGS_HEADERS} account.h)
set (CF_BINDINGS_HEADERS ${CF_BINDINGS_HEADERS} container.h)
set (CF_BINDINGS_SOURCES ${CF_BINDINGS_HEADERS} object.h)

set (CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} account.c)
set (CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} container.c)
set (CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} object.c)

add_library(cf-bindings ${CF_BINDINGS_HEADERS} ${CF_BINDINGS_SOURCES})
set_target_properties(cf-bindings PROPERTIES VERSION ${CF_UTILS_VERSION} SOVERSION 1)

target_link_libraries(cf-bindings uhttpc)

install(TARGETS cf-bindings
  RUNTIME DESTINATION bin COMPONENT Runtime
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib/rackspace/cloudfiles COMPONENT Development
  )

install(TARGETS cf-bindings
  DESTINATION lib EXPORT cf-bindings-lib
  )
install(EXPORT cf-bindings-lib DESTINATION lib/rackspace/cloudfiles)

install(FILES ${CF_BINDINGS_HEADERS} DESTINATION include/rackspace/cloudfiles)
