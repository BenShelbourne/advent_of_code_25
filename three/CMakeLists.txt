cmake_minimum_required(VERSION 3.16)

project(three C)

# Pull every C file in three/ and ../utils/
file(GLOB THREE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.c")

# Build the shared utility library
add_library(utils STATIC ${UTILS_SOURCES})
target_include_directories(utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../utils")

# three executable that links against utils (expects at least three .c in three/)
add_executable(three_program ${THREE_SOURCES})
target_link_libraries(three_program PRIVATE utils)