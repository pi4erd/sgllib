add_executable(window window.cpp)
target_link_libraries(window sgl sglad)
target_include_directories(window PUBLIC ../include ../external/include)
