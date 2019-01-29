cmake_minimum_required(VERSION 3.10.2)
project (image_processing_lib)

#Bring the headers, such as sum.h, into the project
include_directories(include include/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

file(GLOB SOURCES "src/containers/*.cpp" "src/smartResize/*.cpp")

add_library (imageProcessing SHARED ${SOURCES})

install(TARGETS imageProcessing DESTINATION /usr/lib)


