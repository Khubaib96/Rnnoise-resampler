cmake_minimum_required(VERSION 3.16)

set(distribution_DI ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution/test)

include_directories(include)
include_directories(src)
add_library(rnnoise STATIC
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


install(TARGETS rnnoise DESTINATION lib)
