cmake_minimum_required(VERSION 3.13.4)
project(chip8)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -pedantic")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(app ${SOURCES})
target_link_libraries(app ${SDL2_LIBRARIES})
