#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

static bool	init_window(t_game *game);
static void	normalize_window_size(t_game *game);

void	game_init(t_game *game)
{
	size_t	i;

	game->display.height = 0;
	game->display.width = 0;
	game->window.height = 0;
	game->window.width = 0;
	game->window.y_start = 0;
	game->window.x_start = 0;
	game->window.y_end = 0;
	game->window.x_end = 0;
	game->mlx_ptr = NULL;
	game->mlx_win = NULL;
	i = 0;
	while (i < SPRITE_COUNT)
		game->sprites[i++] = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->exit.x = 0;
	game->exit.y = 0;
	game->collectibles_count = 0;
	game->moves_count = 0;
}

bool	game_launch(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (print_err(true, "Mlx init failed"), false);
	if (!init_window(game))
		return (false);
	if (!sprite_load_all(game->sprites, game->mlx_ptr))
		return (false);
	render_init(game);
	if (!mlx_hook(game->mlx_win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, game))
		return (false);
	if (!mlx_hook(game->mlx_win, WINDOW_CLOSE, 0, handle_window_close, game))
		return (false);
	if (!mlx_loop(game->mlx_ptr))
		return (false);
	return (true);
}

# include <stdio.h>	// TMP: remove before submit
static bool	init_window(t_game *game)
{
	mlx_get_screen_size(
		game->mlx_ptr,
		&game->display.width,
		&game->display.height
	);
	if (game->display.width < 0 || game->display.height < 0)
	{
		print_err(false, "mlx_get_screen_size() returned negative values");
		return (false);
	}
	fprintf(stderr, "===> MAP     => width = %4zu | height = %4zu\n", game->map.width, game->map.height);
	fprintf(stderr, "===> DISPLAY => width = %4i | height = %4i\n", game->display.width, game->display.height);
	normalize_window_size(game);
	fprintf(stderr, "===> WINDOW  => width = %4zu | height = %4zu | y_start = %zu | x_start = %zu | y_end = %zu | x_end = %zu\n",
		game->window.width, game->window.height, game->window.y_start, game->window.x_start, game->window.y_end, game->window.x_end);
	game->mlx_win = mlx_new_window(
		game->mlx_ptr,
		(int)game->window.width,
		(int)game->window.height,
		(char *)"so_long"
	);
	if (!game->mlx_win)
		return (print_err(true, "Window init failed"), false);
	return (true);
}

#define WINDOW_PADDING 100
static void	normalize_window_size(t_game *game)
{
	size_t	basic_height;
	size_t	basic_width;

	basic_height = SPRITE_SIZE * game->map.height;
	basic_width = SPRITE_SIZE * game->map.width;
	if (basic_height < (size_t)game->display.height - WINDOW_PADDING && basic_width < (size_t)game->display.width - WINDOW_PADDING)
	{
		game->window.height = basic_height;
		game->window.width = basic_width;
		game->window.y_start = 0;
		game->window.x_start = 0;
		game->window.y_end = game->map.height - 1;
		game->window.x_end = game->map.width - 1;
		return ;
	}
	game->window.height = (size_t)game->display.height - WINDOW_PADDING;
	game->window.width = (size_t)game->display.width - WINDOW_PADDING;
	// TODO: adapt the following values to player position
	game->window.y_start = 0;
	game->window.x_start = 0;
	game->window.y_end = game->window.height / SPRITE_SIZE;
	game->window.x_end = game->window.width / SPRITE_SIZE;
}

void	game_free(t_game *game)
{
	size_t	i;

	if (game->map.grid)
		str_array_free(&game->map.grid);
	if (game->mlx_ptr)
	{
		i = 0;
		while (i < SPRITE_COUNT && game->sprites[i])
		{
			mlx_destroy_image(game->mlx_ptr, game->sprites[i]);
			i++;
		}
		if (game->mlx_win)
			mlx_destroy_window(game->mlx_ptr, game->mlx_win);
		mlx_destroy_display(game->mlx_ptr);
	}
	free(game->mlx_ptr);
}
