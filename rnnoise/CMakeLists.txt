CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(rnnoise)

add_library(rnnoise SHARED
        src/celt_lpc.c
        src/denoise.c
        src/kiss_fft.c
        src/models.c
        src/pitch.c
        src/rnn.c
        src/rnn_data.c
        src/rnn_reader.c
        src/models/bd.c
        src/models/cb.c
        src/models/lq.c
        src/models/mp.c
        src/models/sh.c
        )

target_link_libraries(rnnoise m)
