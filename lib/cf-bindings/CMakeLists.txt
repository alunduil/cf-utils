set (CF_BINDINGS_HEADERS ${CF_BINDINGS_HEADERS} account.h)
set (CF_BINDINGS_HEADERS ${CF_BINDINGS_HEADERS} container.h)

set (CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} account.c)
set (CF_BINDINGS_SOURCES ${CF_BINDINGS_SOURCES} container.c)

add_library(cf-bindings SHARED ${CF_BINDINGS_HEADERS} ${CF_BINDINGS_SOURCES})
set_target_properties(cf-bindings PROPERTIES VERSION ${CF_UTILS_VERSION} SOVERSION 1)

install(TARGETS cf-bindings
  RUNTIME DESTINATION bin COMPONENT Runtime
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib/rackspace/cloudfiles COMPONENT Development)

install(FILES ${CF_BINDINGS_HEADERS} DESTINATION include/rackspace/cloudfiles)

# Object ToDo:
# * URL Encode Names
# * UTF-8 Encode Names
# * 1024 bytes after encoding
# * 5GB limit (segmentation)
# * 90 key/value metadata pairs not exceeding 4KB
