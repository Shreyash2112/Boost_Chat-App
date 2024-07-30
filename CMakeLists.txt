cmake_minimum_required(VERSION 3.20)
project(BOOST_CHAT-APP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(source/Networking)

add_subdirectory(source/Client)
add_subdirectory(source/Server)
