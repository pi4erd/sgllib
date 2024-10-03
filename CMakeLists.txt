cmake_minimum_required(VERSION 3.20)

project(sgllib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

include_directories(external/include)

if(LINUX)
    message("Compiling for Linux")
elseif(WIN32)
    message("Windows not supported, but good luck :)")
else()
    link_directories(/opt/homebrew/lib)
    include_directories(/opt/homebrew/include)
endif()

FILE(GLOB SGL_SOURCE_FILES core/*.cpp)
FILE(GLOB SGL_ADDON_FILES addon/*.cpp)

include_directories(include)

add_library(sgl ${SGL_SOURCE_FILES})

add_library(sglad ${SGL_ADDON_FILES})
set(SGL_LIBRARIES sgl sglad PARENT_SCOPE)

set(SGL_INCLUDE_DIRECTORIES
    ${CMAKE_PROJECT_SOURCE_DIR}/include 
    ${CMAKE_PROJECT_SOURCE_DIR}/external/include
    PARENT_SCOPE
)

target_link_libraries(sgl
    PUBLIC fmt OpenGL::GL glfw GLEW
)

target_link_libraries(sglad
    PUBLIC glm
)

add_subdirectory(examples)
