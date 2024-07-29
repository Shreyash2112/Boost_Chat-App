cmake_minimum_required(VERSION 3.20)
project(Client)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        Networking
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Networking
)
