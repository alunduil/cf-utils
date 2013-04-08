add_library(cf-bindings SHARED
  account.h account.c
  container.h container.c
  )

# Object ToDo:
# * URL Encode Names
# * UTF-8 Encode Names
# * 1024 bytes after encoding
# * 5GB limit (segmentation)
# * 90 key/value metadata pairs not exceeding 4KB
