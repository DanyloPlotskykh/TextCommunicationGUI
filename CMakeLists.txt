cmake_minimum_required(VERSION 3.5)

project(Communication)

find_package(Qt5 REQUIRED COMPONENTS Qml Quick Core Network Widgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(_client)
add_subdirectory(_server)