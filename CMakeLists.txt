cmake_minimum_required(VERSION 3.20)
project(FinalProject)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(src/Domain)
add_subdirectory(src/Application)
add_subdirectory(src/Infrastructure)
add_subdirectory(src/Presentation)