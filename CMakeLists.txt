cmake_minimum_required (VERSION 2.8)
project (persistence_demos)

# modules:
set ( M_EXT_HIJACK "extension_hijack" )
set ( M_COM_HIJACK "com_hijack" )
set ( M_SHIM_PERSIST "shim_persist" )
set ( M_RESTRICTED_DIR "restricted_directory" )

# Add sub-directories
#
add_subdirectory( ${M_EXT_HIJACK} )
add_subdirectory( ${M_COM_HIJACK}/src )
add_subdirectory( ${M_SHIM_PERSIST}/src )
add_subdirectory( ${M_RESTRICTED_DIR}/src )
