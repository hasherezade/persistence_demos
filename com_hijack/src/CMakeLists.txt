cmake_minimum_required ( VERSION 3.0 )
project (COM_Hijack)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
    sysutil.cpp
)

set (hdrs
    resource.h
    sysutil.h
)

set (rsrc
    resource.rc
)

add_executable (COM_Hijack ${rsrc} ${hdrs} ${srcs})
INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
