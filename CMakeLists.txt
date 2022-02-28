cmake_minimum_required(VERSION 3.20)
project(miniRT C)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Werror -Wextra)
#add_compile_options(-O3 -march=native)

INCLUDE_DIRECTORIES(/System/Library/Frameworks)

SET(LIBS mlx ft)

if (APPLE)
    FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
    FIND_LIBRARY(APPKIT_LIBRARY AppKit)
    SET(LIBS ${LIBS} ${OPENGL_LIBRARY} ${APPKIT_LIBRARY})
else ()
    SET(LIBS ${LIBS} Xext X11 m)
endif ()

include_directories(libs/libft/incs includes includes/parsing includes/vector
        includes/rendering/ includes/utils libs/mlx)
link_directories(libs/libft libs/mlx)

add_executable(
        miniRT
        src/main.c
        src/intersections/hit_objs.c
        src/intersections/cylinder.c
        src/intersections/cylinder_caps.c
        src/intersections/plane.c
        src/intersections/sphere.c
        src/intersections/triangle.c
        src/rendering/colors_utils.c
        src/rendering/colors.c
        src/rendering/mlx_img.c
        src/parsing/parser.c
        src/parsing/lights_parser.c
        src/parsing/parse_utils.c
        src/parsing/objects_parser.c
        src/vector/op_vec2.c
        src/vector/op_vec.c
        src/parsing/validate.c
        src/parsing/validate_utils.c
        src/parsing/error.c
        src/hook_utils.c
        src/utils/random.c
        src/rendering/img_threads.c
)

TARGET_LINK_LIBRARIES(miniRT ${LIBS})
