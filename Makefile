# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 13:45:33 by hsabir            #+#    #+#              #
#    Updated: 2022/01/22 14:52:00 by hsabir           ###   ########.fr        #
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
LGNL_NAME = libgnl.a
LMLX = libmlx.a

MAKE = make

# LIBS DIR
LFT_DIR = $(LIB_PATH)/libft
LGNL_DIR = $(LIB_PATH)/get_next_line

# LIBS
LFT = $(LFT_DIR)/$(LFT_NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# Debug flags
DBFLAGS += -g3 -fsanitize=address -v
# LIBS FLAG
IFLAGS += -I ./$(LFT_DIR) -I ./incs -I ./$(LGNL_DIR)/includes

LDFLAGS = -L ./$(LFT_DIR) -L./$(LGNL_DIR)

# SOURCES
SRC_FILES =	$(SRC_PATH)/parser.c

LDLIBS = -lft -lmlx -lgnl

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
#	LDLIBS = -lft -lmlx_Linux
	LDLIBS += -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D OSX
	CCFLAGS += -framework OpenGL -framework AppKit
	LMLX_NAME = $(LMLX_DIR)/$(LMLX_NAME)
	LMLX_DIR = $(LIB_PATH)/mlx
endif

all: $(NAME)

$(NAME): $(LFT_NAME) $(LMLX_NAME)
	$(CC) $(SRC_FILES) $^ -o $@ $(CCFLAGS) $(LDFLAGS) $(LDLIBS) $(IFLAGS) #$(DBFLAGS)

$(LFT_NAME):
	$(MAKE) all -sC $(LFT_DIR)
	cp $(LFT) $(LFT_NAME)

$(LMLX_NAME):
	$(MAKE) all -sC $(LMLX_DIR) 2> /dev/null
	cp $(LMLX) $(LMLX_NAME)

clean:
	$(MAKE) clean -sC $(LFT_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(LMLX_NAME)
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
