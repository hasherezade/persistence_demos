cmake_minimum_required (VERSION 2.8)
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