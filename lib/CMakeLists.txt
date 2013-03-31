add_library(cf-accounts)
add_library(cf-authentication)
add_library(cf-permissions)
add_library(cf-containers) # 500000 per account; No slash in name; 256 bytes after URL encoded name; CDN
add_library(cf-objects) # 1024 bytes after URL encoded name; 5GB limit (segmentation); 90 key/value metadata pairs not exceeding 4KB

add_library(cf-bindings STATIC)

