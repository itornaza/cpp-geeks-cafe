cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(cpp-capstone)

include_directories(include)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
add_executable(a.out src/orders.cpp src/order.cpp src/menu.cpp src/cli.cpp src/main.cpp)