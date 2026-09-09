cmake_minimum_required(VERSION 3.10)
project(BlackStone_Problems)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get all .cpp files in the directory
file(GLOB SOURCES "*.cpp")

# Create an executable for each .cpp file
foreach(SOURCE ${SOURCES})
    # Get the filename without extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    
    # Skip files without main() function
    if(NOT ${EXECUTABLE_NAME} STREQUAL "CMakeLists" AND
       NOT ${EXECUTABLE_NAME} STREQUAL "make_the_string_great" AND
       NOT ${EXECUTABLE_NAME} STREQUAL "reaching_points" AND
       NOT ${EXECUTABLE_NAME} STREQUAL "two_sum")
        add_executable(${EXECUTABLE_NAME} ${SOURCE})
    endif()
endforeach()
