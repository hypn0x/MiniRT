# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 13:45:33 by hsabir            #+#    #+#              #
#   Updated: 2022/02/27 18:17:48 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

CFLAGS := ${CFLAGS}

CC     ?= gcc
LD     ?= gcc

INC_FLAGS := -Ilibs/libft/incs
LIBS := -Llibs/libft -lft -lmlx

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	NPROC := $(shell nproc)
	LIBS += -lmlx -lXext -lX11 -lm
else
	NPROC := $(shell sysctl -n hw.ncpu)
	INC_FLAGS += -Ilibs/mlx
    	LIBS += -Llibs/mlx -framework OpenGL -framework Appkit
endif

MAKEFLAGS += --output-sync=target
MAKEFLAGS += --no-print-directory

NAME ?= miniRT
NAME_BONUS ?= bonusMiniRT

BUILD_DIR ?= ./build
BUILD_DIR_BONUS ?= ./build_bonus
SRC_DIRS ?= ./src
INCLUDE_DIR ?= ./includes

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS_BONUS := $(SRCS:%=$(BUILD_DIR_BONUS)/%.o)

INC_DIRS := $(shell find $(INCLUDE_DIR) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -std=c99 -pedantic
CFLAGS += -O3 -march=native
CFLAGS += -g3
#CFLAGS += -fsanitize=address -v

all:
	@#$(MAKE) -j$(NPROC) -C libs/mlx 2> /dev/null > /dev/null
	@$(MAKE) -j$(NPROC) -C libs/libft libft.a > /dev/null
	@$(MAKE) -j$(NPROC) $(NAME)

bonus:
	@#$(MAKE) -j$(NPROC) -C libs/mlx 2> /dev/null > /dev/null
	@$(MAKE) -j$(NPROC) -C libs/libft libft.a > /dev/null
	@$(MAKE) -j$(NPROC) $(NAME_BONUS) -e CFLAGS="-D SUPERSAMPLING=1"

$(NAME): $(OBJS)
	@echo Linking $@
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	@echo Linking $@
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

$(BUILD_DIR)/%.c.o $(BUILD_DIR_BONUS)/%.c.o: %.c
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CC) -c  $(CFLAGS) $(INC_FLAGS) $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_BONUS)
	@$(MAKE) -C libs/libft clean
	@echo Clean done

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_BONUS)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@$(MAKE) -C libs/libft fclean
	@#$(MAKE) -C libs/mlx clean > /dev/null
	@echo Fclean done

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re
