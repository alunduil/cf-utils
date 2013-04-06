add_library(cf-bindings helpers.c authentication.c account.c container.c)

# Object ToDo:
# * URL Encode Names
# * UTF-8 Encode Names
# * 1024 bytes after encoding
# * 5GB limit (segmentation)
# * 90 key/value metadata pairs not exceeding 4KB
