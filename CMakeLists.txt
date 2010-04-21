project(UTILS)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE
    ${UTILS_SOURCE_DIR}/src/buffer_test.cpp
)

set(HEADERS
    ${UTILS_SOURCE_DIR}/include/buffer.hpp
)

include_directories(
    ${UTIL_SOURCE_DIR}/include
)
                 
add_executable(buffer_test ${SOURCE} ${HEADERS})
