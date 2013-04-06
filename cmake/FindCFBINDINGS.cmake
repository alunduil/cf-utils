#
# Find the Cloud Files Bindings' includes and library
# For more information, see page 46 of Mastering CMake.
#

# This module defines
# CF_BINDINGS_INCLUDE_DIR, where to find container.h, &c.
# CF_BINDINGS_LIBRARIES, the libraries to link against to use Cloud Files.
# CF_BINDINGS_DEFINITIONS, The definitions that should be added before
#                          compilation (i.e.
#                          add_definitions(${CF_BINDINGS_DEFINITIONS})).
# CF_BINDINGS_FOUND, If false, do not try to use Cloud Files.

# also defined, but not for general use are
# CF_BINDINGS_LIBRARY, where to find the cf-bindings library.

find_path(CF_BINDINGS_CF_BINDINGS_INCLUDE_DIR container.h
/usr/local/include
/usr/include
)

find_library(CF_BINDINGS_LIBRARY cf-bindings
/usr/lib
/usr/local/lib
)

if (CF_BINDINGS_LIBRARY)
  if (CF_BINDINGS_CF_BINDINGS_INCLUDE_DIR)
    set (CF_BINDINGS_INCLUDE_DIR ${CF_BINDINGS_CF_BINDINGS_INCLUDE_DIR})
    set (CF_BINDINGS_LIBRARIES ${CF_BINDINGS_LIBRARY})
    set (CF_BINDINGS_FOUND "YES")
  endif(CF_BINDINGS_CF_BINDINGS_INCLUDE_DIR)
endif(CF_BINDINGS_LIBRARY
