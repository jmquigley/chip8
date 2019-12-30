cmake_minimum_required(VERSION 3.13.4)
project(chip8)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_compile_options("-Wall" "-pedantic" "$<$<CONFIG:DEBUG>:-O0;-g3>")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(app ${SOURCES})
target_link_libraries(app ${SDL2_LIBRARIES})
