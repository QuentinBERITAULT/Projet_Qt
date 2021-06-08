cmake_minimum_required(VERSION 3.10)
project(beritault)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h)

add_executable(beritault ${sourceCode} src/User.h src/User.cpp)

target_link_libraries(beritault Qt5::Widgets)