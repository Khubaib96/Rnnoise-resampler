cmake_minimum_required(VERSION 3.16)
project(finalCode)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(rnnoise)

add_subdirectory(resampling)

add_executable(finalCode main.cpp)

target_link_libraries(finalCode rnnoise resampling)