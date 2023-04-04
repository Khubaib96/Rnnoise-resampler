cmake_minimum_required(VERSION 3.16)
#project(resampling )

#set(CMAKE_CXX_STANDARD 14)

add_library(resampling STATIC casyi.cpp
        cmlri.cpp
        createFilter.cpp
        firls.cpp
        gammaln.cpp
        ipermute.cpp
        mldivide.cpp
        mod.cpp
        resampling.cpp
        resampling_data.cpp
        resampling_initialize.cpp
        resampling_rtwutil.cpp
        resampling_terminate.cpp
        rtGetInf.cpp
        rtGetNaN.cpp
        rt_nonfinite.cpp
        xgeqp3.cpp
        xnrm2.cpp
        )

