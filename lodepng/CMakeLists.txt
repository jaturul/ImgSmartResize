cmake_minimum_required(VERSION 3.10.2)
project (lodepng_lib)

#Bring the headers and libraries into the project
include_directories(include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

#However, the file(GLOB...) allows for wildcard additions:
set(SOURCES "src/lodepng.cpp" )

add_library (lodepng SHARED ${SOURCES})
