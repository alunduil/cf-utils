add_library(helpers STATIC helpers.c)

add_library(accounts)
add_library(authentication STATIC authentication.c)
add_library(permissions)
add_library(containers) # 500000 per account; No slash in name; 256 bytes after URL encoded name; CDN
# URI; Expires; Cache-Control

add_library(objects) # 1024 bytes after URL encoded name; 5GB limit (segmentation); 90 key/value metadata pairs not exceeding 4KB

add_library(bindings STATIC)
