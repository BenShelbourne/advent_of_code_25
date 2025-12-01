cmake_minimum_required(VERSION 3.16)

project(one C)

# Pull every C file in one/ and ../utils/
file(GLOB ONE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.c")

# Build the shared utility library
add_library(utils STATIC ${UTILS_SOURCES})
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../utils")

# One executable that links against utils (expects at least one .c in one/)
add_executable(one_program ${ONE_SOURCES})
target_link_libraries(one_program PRIVATE utils)