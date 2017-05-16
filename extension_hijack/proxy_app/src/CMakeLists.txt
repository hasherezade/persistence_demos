cmake_minimum_required (VERSION 2.8)
project (ProxyApp)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

set (srcs
    main.cpp
)

add_executable (ProxyApp ${srcs})