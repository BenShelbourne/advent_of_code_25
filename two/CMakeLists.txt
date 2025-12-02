cmake_minimum_required(VERSION 3.16)

project(two C)

# Pull every C file in two/ and ../utils/
file(GLOB TWO_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.c")

# Build the shared utility library
add_library(utils STATIC ${UTILS_SOURCES})
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../utils")

# two executable that links against utils (expects at least two .c in two/)
add_executable(two_program ${TWO_SOURCES})
target_link_libraries(two_program PRIVATE utils)