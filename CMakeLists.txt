cmake_minimum_required(VERSION 3.24)

project(BinaryStars CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Set source directory before any include path usage.
set(SRC_DIR src)

# Pick a default build type early so dependencies see it during configuration.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    message(STATUS "Building ${PROJECT_NAME} in Release mode")
endif()

# Dependencies
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)

FetchContent_MakeAvailable(raylib)

# Add all source files to the project
include_directories(${SRC_DIR})

# Add all header files to the project
include_directories(${INC_DIR})

# Recursively find all header + implementation files
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HPP_HEADERS CONFIGURE_DEPENDS "${SRC_DIR}/*.hpp")

include_directories(${SRC_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building ${PROJECT_NAME} in Debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${HPP_HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC
                        raylib
                        )

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
