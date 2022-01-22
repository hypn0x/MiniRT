# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 13:45:33 by hsabir            #+#    #+#              #
#    Updated: 2022/01/22 14:33:05 by hsabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# PATHS
INC_PATH = incs
SRC_PATH = srcs
OBJ_PATH = objs
LIB_PATH = libs

# LIBS NAME
LFT_NAME = libft.a
LMLX_MACOS = libmlx.a
LMLX_LINUX = libmlx.a

MAKE = make

# LIBS DIR
LFT_DIR = $(LIB_PATH)/libft
LMLX_DIR_LINUX = $(LIB_PATH)/mlx_linux
LMLX_DIR_MACOS = $(LIB_PATH)/mlx_macos

# LIBS
LFT = $(LFT_DIR)/$(LFT_NAME)
LMLX = $(LMLX_DIR)/$(LMLX_NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# Debug flags
CFLAGS += -g3 -fsanitize=address -v
# LIBS FLAG
CFLAGS += -I ./$(LFT_DIR)/incs -I ./$(LMLX_DIR) -I ./incs

LDFLAGS = -L ./

# SOURCES
SRC_FILES =	$(SRC_PATH)/main.c

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
	LDLIBS = -lft -lmlx_Linux
	LDLIBS += -lXext -lX11 -lm -lz
	LMLX_NAME = $(LMLX_NAME_LINUX)
	LMLX_DIR = $(LMLX_DIR_LINUX)
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D OSX
	CCFLAGS += -framework OpenGL -framework AppKit
	LDLIBS = -lft -lmlx
	LMLX_NAME = $(LMLX_MACOS)
	LMLX_DIR = $(LMLX_DIR_MACOS)
endif

all: $(NAME)

$(NAME): $(LFT_NAME) $(LMLX_NAME)
	$(CC) $(SRC_FILES) $^ -o $@ $(CCFLAGS) $(LDFLAGS) $(LDLIBS)

$(LFT_NAME):
	$(MAKE) all -sC $(LFT_DIR)
	cp $(LFT) $(LFT_NAME)

$(LMLX_NAME):
	$(MAKE) all -sC $(LMLX_DIR) 2> /dev/null
	cp $(LMLX) $(LMLX_NAME)

clean:
	$(MAKE) clean -sC $(LFT_DIR)
	$(MAKE) clean -sC $(LMLX_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(LMLX_NAME)
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
