cmake_minimum_required(VERSION 3.20)
project(miniRT C)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 99)

#add_compile_options(-Wall -Werror -Wextra)
execute_process(COMMAND uname -s OUTPUT_VARIABLE OS)

SET(LIBS mlx ft)
add_link_options(-lXext -lX11 -lm -lbsd)

if ($OS STREQUAL "Linux")
    add_link_options(-lXext -lX11 -lm -lbsd)
else ()
#    FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
#    FIND_LIBRARY(APPKIT_LIBRARY AppKit)
#    SET(LIBS ${OPENGL_LIBRARY} ${APPKIT_LIBRARY})
endif ()

include_directories(libs/libft/incs includes includes/parsing includes/vector libs/mlx)
link_directories(libs/libft libs/mlx)

add_executable(
        miniRT
        src/main.c
        src/parsing/parser.c
        src/parsing/lights_parser.c
        src/parsing/parse_utils.c
        src/parsing/objects_parser.c
        src/vector/op_vec_double.c
        src/vector/op_vec.c
        src/parsing/validate.c
        src/parsing/validate_utils.c
        src/hook_utils.c
)

TARGET_LINK_LIBRARIES(miniRT ft mlx ${LIBS})
