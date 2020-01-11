cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(cpp-capstone)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

