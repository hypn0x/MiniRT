SHELL = /bin/sh

CFLAGS := ${CFLAGS}

CC     ?= gcc
LD     ?= gcc

NAME   ?= libgnl.a

DIST_DIR ?= ./dist
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS += $(addprefix -I,$(INC_DIRS))

PATH_LIB = $(DIST_DIR)/$(NAME)
CFLAGS += -Wall -Wextra -Werror
#CFLAGS += -O2 -march=native
#CFLAGS += -g

$(PATH_LIB): $(OBJS)
	@mkdir -p $(DIST_DIR)
	@$(AR) rcs $(PATH_LIB) $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $< -o $@

all: $(PATH_LIB)

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -rf $(DIST_DIR)

re: fclean all

.PHONY: all clean fclean re