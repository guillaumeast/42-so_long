NAME			:= so_long
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -O2 -g3

SANITIZE ?= 1

ifeq ($(SANITIZE),1)
	CFLAGS += -fsanitize=address
endif

# ================= OS SWITCH ================= #

UNAME_S			:= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	MLX_DIR		:= mlx-mac
	MLX_LIBS	:= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S),Linux)
	MLX_DIR		:= mlx-linux
	MLX_LIBS	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else
	$(error Unsupported OS)
endif

# ================== SOURCES ================== #

SRCS			:= $(wildcard logs/*.c) $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)

LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a

LIBS			:= $(LIBFT) $(MLX_LIBS)

INCLUDES		:= \
	-I$(LIBFT_DIR) \
	-I$(MLX_DIR) \
	-Ilogs \
	-Isrc \
	-Isrc/1_view \
	-Isrc/1_view/0_fps \
	-Isrc/1_view/1_sprite_set \
	-Isrc/1_view/2_position \
	-Isrc/1_view/3_size \
	-Isrc/1_view/4_texture \
	-Isrc/1_view/5_object \
	-Isrc/1_view/apple

OBJ_DIR			:= obj
OBJS			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

MY_TESTER		:= ./tests/test.zsh

# ================= RULES ================= #

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: re
	@$(MY_TESTER)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all test clean fclean re