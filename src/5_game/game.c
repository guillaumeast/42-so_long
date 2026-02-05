#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

# include "logs.h"

static bool	init_mlx(t_game *game);

void	game_init(t_game *game)
{
	size_t	i;

	game->context = NULL;
	game->window = NULL;
	i = 0;
	while (i < SPRITE_COUNT)
	{
		game->sprites[i] = NULL;
		i++;
	}
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
	print_title("game_launch()");
	if (!init_mlx(game))
		return (false);
	print_pass("game inited\n");
	render_init(game);
	print_pass("render inited\n");
	mlx_hook(game->window, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, game);
	mlx_hook(game->window, WINDOW_CLOSE, 0, handle_window_close, game);
	print_pass("hooks inited\n");
	print_info("launching game...\n");
	mlx_loop(game->context);
	return (true);
}

static bool	init_mlx(t_game *game)
{
	game->context = mlx_init();
	if (!game->context)
		return (print_err(true, "Mlx init failed"), false);
	print_pass("context inited\n");
	game->window = mlx_new_window(
		game->context,
		(int)(SPRITE_SIZE * game->map.width),
		(int)(SPRITE_SIZE * game->map.height),
		(char *)"so_long"
	);
	if (!game->window)
	{
		mlx_destroy_display(game->context);
		return (print_err(true, "Window init failed"), false);
	}
	print_pass("window inited (%zu x %zu)\n", SPRITE_SIZE * game->map.width, SPRITE_SIZE * game->map.height);
	if (!sprite_load_all(game->sprites, game->context))
	{
		mlx_destroy_window(game->context, game->window);
		mlx_destroy_display(game->context);
		return (false);
	}
	print_pass("sprites loaded\n");
	return (true);
}

void	game_free(t_game *game)
{
	size_t	i;

	if (game->map.grid)
		str_array_free(&game->map.grid);
	if (game->context)
	{
		i = 0;
		while (i < SPRITE_COUNT && game->sprites[i])
		{
			mlx_destroy_image(game->context, game->sprites[i]);
			i++;
		}
		if (game->window)
			mlx_destroy_window(game->context, game->window);
		mlx_destroy_display(game->context);
	}
}
