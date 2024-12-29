cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MyProject main.cpp)

# Add the src directory to the include directories
target_include_directories(MyProject PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add the source files from the inc directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/inc/*.cpp")

# Add the source files to the executable
target_sources(MyProject PRIVATE ${SOURCES})

# Link with the filesystem library if necessary
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_libraries(MyProject PRIVATE stdc++fs)
endif()
