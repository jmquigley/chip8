cmake_minimum_required(VERSION 3.13.4)
project(chip8)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(chip8 ${SOURCES})
target_link_libraries(chip8 SDL2)
