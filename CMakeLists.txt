cmake_minimum_required(VERSION 2.8)
project(cpp-synchronized)

# Basic variables
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")
SET (INCLUDES "${MAINFOLDER}/include")

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(${INCLUDES})

add_subdirectory(src)
#add_subdirectory(test)
