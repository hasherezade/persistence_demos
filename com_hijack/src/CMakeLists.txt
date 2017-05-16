cmake_minimum_required (VERSION 2.8)
project (COM_Hijack)

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