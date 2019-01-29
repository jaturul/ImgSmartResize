cmake_minimum_required(VERSION 3.10.2)
project (imgSmartResize)

#Bring the headers and libraries into the project
set ( PROJECT_LINK_LIBS liblodepng.so libimageProcessing.so )
link_directories(${CMAKE_BINARY_DIR}/../lib ${CMAKE_BINARY_DIR}/../thirdparty/lodepng/lib)
include_directories(include thirdparty)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/main.cpp src/sum.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable (imgSmartResize ${SOURCES})
target_link_libraries(imgSmartResize ${PROJECT_LINK_LIBS})
