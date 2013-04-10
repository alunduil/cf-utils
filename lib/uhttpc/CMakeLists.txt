set (UHTTPC_HEADERS ${UHTTPC_HEADERS} request.h)
set (UHTTPC_HEADERS ${UHTTPC_HEADERS} response.h)
set (UHTTPC_HEADERS ${UHTTPC_HEADERS} actions.h)

set (UHTTPC_SOURCES ${UHTTPC_SOURCES} request.c)
set (UHTTPC_SOURCES ${UHTTPC_SOURCES} response.c)
set (UHTTPC_SOURCES ${UHTTPC_SOURCES} actions.c)

add_library(uhttpc SHARED ${UHTTPC_HEADERS} ${UHTTPC_SOURCES})
set_target_properties(uhttpc PROPERTIES VERSION ${CF_UTILS_VERSION} SOVERSION 1)

install(TARGETS uhttpc
  RUNTIME DESTINATION bin COMPONENT Runtime
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib/uhttpc COMPONENT Development
  )

install(TARGETS uhttpc
  DESTINATION lib EXPORT uhttpc-lib
  )
install(EXPORT uhttpc-lib DESTINATION lib/uhttpc)

install(FILES ${UHTTPC_HEADERS} DESTINATION include/uhttpc)
