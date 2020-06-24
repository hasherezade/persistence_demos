cmake_minimum_required (VERSION 2.8)
project (extension_hijack)

# modules:
set ( M_EXT_HIJACKER_APP "hijacker_app" )
set ( M_EXT_HIJACKER_PROXY "proxy_app" )

# Add sub-directories
#
add_subdirectory( ${M_EXT_HIJACKER_APP}/src )
add_subdirectory( ${M_EXT_HIJACKER_PROXY}/src )
