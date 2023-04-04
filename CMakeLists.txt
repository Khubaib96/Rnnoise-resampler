cmake_minimum_required(VERSION 3.16)
project(finalCode)

set(CMAKE_CXX_STANDARD 17)

include_directories(rnnoise)
add_subdirectory(rnnoise)

include_directories(resampling)
add_subdirectory(resampling)

add_executable(finalCode main.cpp)

target_include_directories(finalCode PUBLIC rnnoise resampling)
target_link_libraries(finalCode PUBLIC rnnoise resampling)
