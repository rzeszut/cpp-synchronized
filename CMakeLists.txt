cmake_minimum_required(VERSION 2.8)
project(cpp-synchronized)

# Set this to on (-Dtest=ON) to compile tests as well
option(test "Build all tests." OFF)

# Set this to ON to build examples as well.
option(examples "Build examples." OFF)

# Basic variables
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")
SET (INCLUDES "${MAINFOLDER}/include")

# Compiler settings
add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(${INCLUDES})
add_subdirectory(src)

# Testing
if (test)
    # Add gtest to the build path
    add_subdirectory("thirdparty/gtest-1.7.0")

    enable_testing()

    # Include gtest library
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Include library tests
    add_subdirectory(test)
endif ()

if (examples)
    add_subdirectory(examples)
endif ()
