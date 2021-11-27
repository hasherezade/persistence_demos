cmake_minimum_required ( VERSION 2.8...3.21 )
project (restricted_directory)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
    install.cpp
)

set (hdrs
    resource.h
    install.h
)

set (rsrc
    resource.rc
)

add_executable (${PROJECT_NAME} ${rsrc} ${hdrs} ${srcs})
INSTALL( TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT ${PROJECT_NAME} )
