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

SRCS			:= $(wildcard logs/*.c) $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c)

LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a

LIBS			:= $(LIBFT) $(MLX_LIBS)

INCLUDES		:= \
	-I$(LIBFT_DIR) \
	-I$(MLX_DIR) \
	-Ilogs \
	-Isrc \
	-Isrc/0_clock \
	-Isrc/0_my_mlx \
	-Isrc/1_model \
	-Isrc/2_view \
	-Isrc/2_view/1_mlx \
	-Isrc/2_view/2_skin \
	-Isrc/2_view/3_element \
	-Isrc/2_view/4_render \
	-Isrc/3_controller \
	-Isrc/4_components

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