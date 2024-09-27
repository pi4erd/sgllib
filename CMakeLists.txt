cmake_minimum_required(VERSION 3.20)

project(sgllib VERSION 0.1.0)

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

FILE(GLOB SGL_SOURCE_FILES core/*.cpp)
FILE(GLOB SGL_ADDON_FILES addon/*.cpp)

include_directories(include)

add_library(sgl ${SGL_SOURCE_FILES})

add_library(sglad ${SGL_ADDON_FILES})
set(SGL_LIBRARIES sgl sglad PARENT_SCOPE)

set(SGL_INCLUDE_DIRECTORIES include PARENT_SCOPE)

target_link_libraries(sgl
    PUBLIC fmt OpenGL::GL glfw3 GLEW
)
