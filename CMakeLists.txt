cmake_minimum_required(VERSION 3.20)
project(miniRT C)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Werror -Wextra)
add_link_options(-lmlx -lXext -lX11 -lm -lbsd)

include_directories(libs/libft libs/get_next_line/includes)
link_directories(libs/libft libs/get_next_line)

add_executable(miniRT
        src/main.c
        src/parser.c
        includes/parser.h
)

TARGET_LINK_LIBRARIES(miniRT mlx)
TARGET_LINK_LIBRARIES(miniRT ft)
TARGET_LINK_LIBRARIES(miniRT gnl)