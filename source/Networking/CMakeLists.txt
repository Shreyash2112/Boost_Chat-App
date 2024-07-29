cmake_minimum_required(VERSION 3.20)
project(Networking)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Boost package using the new CMake configuration
find_package(Boost 1.85.0)

# Globs all Source files
file(GLOB SOURCES src/* src/*/* src/*/*/* .cpp)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${Boost_LIBRARIES}
)

