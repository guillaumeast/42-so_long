NAME		:= so_long
CC			:= cc
CFLAGS		= -Wall -Wextra -Werror -O2 -g3 -fsanitize=address

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

LIBS		:= $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS		:= \
	$(wildcard logs/*.c) \
	$(wildcard src/*.c) \
	$(wildcard src/*/*.c)
INCLUDES	:= \
	-Imlx \
	-I$(LIBFT_DIR) \
	-Ilogs \
	-Isrc \
	-Isrc/1_map \
	-Isrc/2_sprites \
	-Isrc/3_render \
	-Isrc/4_hooks \
	-Isrc/5_game

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

MY_TESTER	:= ./tests/test.zsh

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