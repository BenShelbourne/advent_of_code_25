cmake_minimum_required(VERSION 3.16)

project(four C)

# Pull every C file in four/ and ../utils/
file(GLOB FOUR_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.c")

# Build the shared utility library
add_library(utils STATIC ${UTILS_SOURCES})
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../utils")

# four executable that links against utils (expects at least four .c in four/)
add_executable(four_program ${FOUR_SOURCES})
target_link_libraries(four_program PRIVATE utils)