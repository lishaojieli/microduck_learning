cmake_minimum_required(VERSION 3.16)

project(microduck_day02)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    microduck_day02
    src/main.cpp
    src/servo.cpp
    src/robot.cpp
    src/controller.cpp
)

target_include_directories(
    microduck_day02
    PRIVATE
    include
)