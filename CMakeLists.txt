project(COW_UTILS)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE Debug)

ENABLE_TESTING()

set(TEST_SOURCES
    ${COW_UTILS_SOURCE_DIR}/test/buffer_test.cpp
)

set(BUFFER_HEADERS
    ${COW_UTILS_SOURCE_DIR}/buffer/include
)

include_directories(
    ${BUFFER_HEADERS}
)
                 
add_executable(buffer_test ${TEST_SOURCES} ${BUFFER_HEADERS})
ADD_TEST(BufferTest buffer_test)
