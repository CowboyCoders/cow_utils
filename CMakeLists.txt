project(COW_UTILS)
cmake_minimum_required(VERSION 2.6)

set(PACKETIZER_SOURCE_DIR ${COW_UTILS_SOURCE_DIR}/packetizer)
set(BUFFER_SOURCE_DIR ${COW_UTILS_SOURCE_DIR}/buffer)

set(BUFFER_TEST_SOURCE
    ${COW_UTILS_SOURCE_DIR}/test/buffer_test.cpp
)

set(BUFFER_HEADERS
    ${BUFFER_SOURCE_DIR}/include/buffer.hpp
)

set(PACKETIZER_SOURCE
    ${PACKETIZER_SOURCE_DIR}/src/packetizer.cpp
    ${PACKETIZER_SOURCE_DIR}/src/movie_packet.cpp
    ${PACKETIZER_SOURCE_DIR}/src/sync_packet.cpp
)

set(PACKETIZER_HEADERS
    ${PACKETIZER_SOURCE_DIR}/include/packetizer.hpp
    ${PACKETIZER_SOURCE_DIR}/include/movie_packet.hpp
    ${PACKETIZER_SOURCE_DIR}/include/sync_packet.hpp
)

set(PACKETIZER_TEST_SOURCE
    ${PACKETIZER_SOURCE}
    ${COW_UTILS_SOURCE_DIR}/test/packetizer_test.cpp
)

include_directories(
    ${BUFFER_SOURCE_DIR}/include
    ${PACKETIZER_SOURCE_DIR}/include
)

set(CMAKE_BUILD_TYPE Debug)

# add all warnings if debug mode is set
if(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

# unit tests follows
ENABLE_TESTING()

add_executable(buffer_test ${BUFFER_TEST_SOURCE} ${BUFFER_HEADERS})
ADD_TEST(BufferTest buffer_test) 

add_executable(packetizer_test ${PACKETIZER_TEST_SOURCE} ${PACKETIZER_HEADERS})
ADD_TEST(PacketizerTest packetizer_test)

# shared library
add_library(cow_utils SHARED ${PACKETIZER_SOURCE} ${PACKETIZER_HEADERS})
