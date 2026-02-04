#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

static bool	init_mlx(t_game *game, t_map *map, t_object *player);

static void	game_init(t_game *game)
{
	map_init(&game->map);
	game->context = NULL;
	game->window = NULL;
	sprite_init_all(game->sprites);
	game->moves_count = 0;
}

bool	game_launch(t_game *game, t_map *map, t_object *player)
{
	game_init(game);
	if (!init_mlx(game, map, player))
		return (false);
	render_init(game);
	mlx_hook(game->window, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, game);
	mlx_hook(game->window, WINDOW_CLOSE, 0, handle_window_close, game);
	mlx_loop(game->context);
	return (true);
}

/*
*	Populates the game struct with all required data.
*
*	Does NOT free map and player on failure.
*
*	WARNING: map and player must be loaded before calling this function.
*/
static bool	init_mlx(t_game *game, t_map *map, t_object *player)
{
	game->context = mlx_init();
	if (!game->context)
		return (print_err(true, "Mlx init failed"), false);
	game->window = mlx_new_window(
		game->context,
		(int)(SPRITE_SIZE * map->width),
		(int)(SPRITE_SIZE * map->height),
		(char *)"so_long"
	);
	if (!game->window)
	{
		// mlx_destroy_display(game->context);	// TODO: Uncomment before submit (only available in Linux mlx)
		return (print_err(true, "Window init failed"), false);
	}
	if (!sprite_load_all(game->sprites, game->context))
	{
		mlx_destroy_window(game->context, game->window);
		// mlx_destroy_display(game->context);	// TODO: Uncomment before submit (only available in Linux mlx)
		return (false);
	}
	game->map = *map;
	game->player = *player;
	return (true);
}

void	game_free(t_game *game)
{
	map_free(&game->map);
	sprite_free_all(game->sprites, game->context);
	if (game->context && game->window)
		mlx_destroy_window(game->context, game->window);
	// TODO: Uncomment before submit (only available in Linux mlx)
	// if (game->context)
	// 	mlx_destroy_display(game->context);
	exit(EXIT_SUCCESS);
}
