#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

static inline bool	init_modified_cells(t_game *game);

void	game_init(t_game *game)
{
	game->mlx_ptr = NULL;
	sprites_init_all(&game->sprites);
	map_init(&game->map);
	window_init(&game->window);
	game->modified_cells = NULL;
	game->modified_cells_count = 0;
	game->moves_count = 0;
}

bool	game_launch(t_game *game, char *map_path)
{
	game_init(game);
	if (!map_load(&game->map, map_path))
		return (false);
	if (!init_modified_cells(game))
		return (false);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (print_err(true, "Mlx init failed"), false);
	if (!sprites_load_all(game->mlx_ptr, &game->sprites))
		return (false);
	if (!window_load(game->mlx_ptr, &game->window, &game->map))
		return (false);
	if (!mlx_hook(game->window.mlx_win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, game))
		return (print_err(true, "mlx_hook() failed"), false);
	if (!mlx_hook(game->window.mlx_win, WINDOW_CLOSE, 0, handle_window_close, game))
		return (print_err(true, "mlx_hook() failed"), false);
	mlx_loop_hook(game->mlx_ptr, render_frame, game);
	game->window.moved = true;
	mlx_loop(game->mlx_ptr);
	return (true);
}

static inline bool	init_modified_cells(t_game *game)
{
	size_t	cells_count;

	cells_count = (size_t)(game->map.height * game->map.width);
	game->modified_cells = malloc(cells_count * sizeof * game->modified_cells);
	if (!game->modified_cells)
	{
		fprint_err(true, "Unable to malloc modified cells",
			" with size %zu", cells_count * sizeof * game->modified_cells);
		return (false);
	}
	return (true);
}

void	game_win(t_game *game)
{
	mlx_loop_end(game->mlx_ptr);
}

void	game_free(t_game *game)
{
	sprites_free_all(game->mlx_ptr, &game->sprites);
	map_free(&game->map);
	window_free(game->mlx_ptr, &game->window);
	if (game->modified_cells)
		free(game->modified_cells);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	game_init(game);
}
