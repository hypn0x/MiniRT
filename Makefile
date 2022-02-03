# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 13:45:33 by hsabir            #+#    #+#              #
#   Updated: 2022/02/03 19:29:04 by                  ###   ########.fr       # #
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
	LIBS += -lmlx -lXext -lX11 -lm -lbsd
else
	NPROC := $(shell sysctl -n hw.ncpu)
	INC_FLAGS += -Ilibs/mlx
    	LIBS += -Llibs/mlx -framework OpenGL -framework Appkit
endif

MAKEFLAGS += --output-sync=target
MAKEFLAGS += --no-print-directory

NAME ?= miniRT

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
INCLUDE_DIR ?= ./includes

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(INCLUDE_DIR) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

#CFLAGS += -Wall -Wextra -Werror
CFLAGS += -std=c99 -pedantic
#CFLAGS += -O2 -march=native
#CFLAGS += -g3
#CFLAGS += -fsanitize=address -v

all:
	@$(MAKE) -j$(NPROC) $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libs/libft libft.a
	@echo Libft done
	@echo GNL done
	@echo Linking $@
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CC) -c  $(CFLAGS) $(INC_FLAGS) $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C libs/libft clean
	@echo Clean done

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C libs/libft fclean
	@echo Fclean done

re: fclean
	@$(MAKE) -j$(NPROC) $(NAME)

.PHONY: all clean fclean re
