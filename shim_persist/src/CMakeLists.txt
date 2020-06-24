cmake_minimum_required (VERSION 2.8)
project (shim_demo)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
    elevate.cpp
)

set (hdrs
    resource.h
    elevate.h
)

set (rsrc
    resource.rc
)

add_executable (shim_demo ${rsrc} ${hdrs} ${srcs})
INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
