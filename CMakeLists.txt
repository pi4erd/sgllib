cmake_minimum_required(VERSION 3.20)

project(sgllib VERSION 0.0.0)

FILE(GLOB SGL_SOURCE_FILES core/*.cpp)
FILE(GLOB SGL_ADDON_FILES addon/*.cpp)

add_library(sgl ${SGL_SOURCE_FILES})

if(SGL_BUILD_ADDON)
    add_library(sglad ${SGL_SOURCE_FILES})
    set(SGL_LIBRARIES sgl sglad)
else()
    set(SGL_LIBRARIES sgl)
endif()

set(SGL_INCLUDE_DIRECTORIES include)
