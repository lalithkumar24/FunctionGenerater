cmake_minimum_required(VERSION 4.2)
project(Function_Generater LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(Function_Generater
        main.cpp
        lib/tinyexpr.cpp
        lib/tinyexpr.h
        main.h
        defs.h
)

target_link_libraries(Function_Generater PRIVATE SDL2::SDL2)
