#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

static bool	init_window(t_game *game);

void	game_init(t_game *game)
{
	size_t	i;

	game->display.height = 0;
	game->display.width = 0;
	game->window.height = 0;
	game->window.width = 0;
	game->window.top_left_y = 0;
	game->window.top_left_x = 0;
	game->window.bot_right_y = 0;
	game->window.bot_right_x = 0;
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

static bool	init_window(t_game *game)
{
	if (!mlx_get_screen_size(
		game->mlx_ptr,
		&game->display.width,
		&game->display.height
	))
		return (false);
	if (game->display.width < 0 || game->display.height < 0)
	{
		print_err(false, "mlx_get_screen_size() returned negative values");
		return (false);
	}
	game->mlx_win = mlx_new_window(
		game->mlx_ptr,
		(int)(SPRITE_SIZE * game->map.width),
		(int)(SPRITE_SIZE * game->map.height),
		(char *)"so_long"
	);
	if (!game->mlx_win)
		return (print_err(true, "Window init failed"), false);
	return (true);
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
