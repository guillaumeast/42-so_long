#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

static inline bool	init_modified_cells(t_game *game);

bool	game_launch(t_game *game)
{
	if (!init_modified_cells(game))
		return (false);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (print_err(true, "Mlx init failed"), false);
	if (!sprite_load_all(game))
		return (false);
	if (!window_init(game))
		return (false);
	if (!mlx_hook(game->mlx_win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, game))
		return (print_err(true, "mlx_hook() failed"), false);
	if (!mlx_hook(game->mlx_win, WINDOW_CLOSE, 0, handle_window_close, game))
		return (print_err(true, "mlx_hook() failed"), false);
	if (mlx_loop_hook(game->mlx_ptr, render_frame, game))
		return (print_err(true, "mlx_loop_hook() failed"), false);
	render_hud_init(game);
	game->window.moved = true;
	if (!mlx_loop(game->mlx_ptr))
		return (print_err(true, "mlx_loop() failed"), false);
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
