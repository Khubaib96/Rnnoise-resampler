cmake_minimum_required(VERSION 3.16)
project(finalCode)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(rnnoise)

add_subdirectory(resampling)

add_executable(finalCode main.cpp
        rnnoise/src/celt_lpc.c
        rnnoise/src/denoise.c
        rnnoise/src/kiss_fft.c
        rnnoise/src/models.c
        rnnoise/src/pitch.c
        rnnoise/src/rnn.c
        rnnoise/src/rnn_data.c
        rnnoise/src/rnn_reader.c
        rnnoise/src/models/bd.c
        rnnoise/src/models/cb.c
        rnnoise/src/models/lq.c
        rnnoise/src/models/mp.c
        rnnoise/src/models/sh.c)

target_link_libraries(finalCode ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/rnnoise/librnnoise.so ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/resampling/libresampling.so)
