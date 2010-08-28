project(PACKETIZER)
cmake_minimum_required(VERSION 2.8)
set(UTILS_SOURCE_DIR ../utils/)
set(LIBCOW_SOURCE_DIR ../libcow/)

if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -DDEBUG")
endif(UNIX)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE
    ${PACKETIZER_SOURCE_DIR}/src/packetizer.cpp
    ${PACKETIZER_SOURCE_DIR}/src/movie_packet.cpp
    ${PACKETIZER_SOURCE_DIR}/src/sync_packet.cpp
    ${PACKETIZER_SOURCE_DIR}/src/packetizer_test.cpp
)

set(HEADERS
    ${PACKETIZER_SOURCE_DIR}/include/packetizer.hpp
    ${PACKETIZER_SOURCE_DIR}/include/movie_packet.hpp
    ${PACKETIZER_SOURCE_DIR}/include/sync_packet.hpp
)

include_directories(
    ${PACKETIZER_SOURCE_DIR}/include
    ${UTILS_SOURCE_DIR}/include
    ${LIBCOW_SOURCE_DIR}/include
)
                 
add_executable(packetizer_test ${SOURCE} ${HEADERS})
