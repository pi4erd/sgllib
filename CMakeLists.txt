cmake_minimum_required(VERSION 3.20)

project(sgllib VERSION 0.0.0)

FILE(GLOB SGL_SOURCE_FILES core/*.cpp)
FILE(GLOB SGL_ADDON_FILES addon/*.cpp)

include_directories(include)

add_library(sgl ${SGL_SOURCE_FILES})

add_library(sglad ${SGL_SOURCE_FILES})
set(SGL_LIBRARIES sgl sglad)

set(SGL_INCLUDE_DIRECTORIES include)
