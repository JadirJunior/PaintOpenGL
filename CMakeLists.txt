cmake_minimum_required(VERSION 3.29)
project(PaintOpenGL C)


set(CMAKE_C_STANDARD 11)


include_directories(D:/minGw/include/GL)
link_directories(D:/minGw/lib)

add_executable(PaintOpenGL main.c
        DBForms.c
        headers/figure.h
        headers/DBForms.h
        figure.c)

target_link_libraries(PaintOpenGL opengl32 freeglut_static glu32 freeglut)
