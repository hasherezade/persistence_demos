cmake_minimum_required (VERSION 2.8)
project (shim_demo)

set (srcs
    main.cpp
)

set (hdrs
    resource.h
)

set (rsrc
    resource.rc
)

add_executable (shim_demo ${rsrc} ${hdrs} ${srcs})