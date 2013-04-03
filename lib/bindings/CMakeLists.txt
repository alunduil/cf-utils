add_library(cf-bindings helpers.c authentication.c account.c container.c)

# URL encode names first! UTF-8!
# Containers: 500000 per account; No slash in name; 256 bytes after URL encoded name; CDN
# URI; Expires; Cache-Control
# Objects: 1024 bytes after URL encoded name; 5GB limit (segmentation); 90 key/value metadata pairs not exceeding 4KB
