#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>

void	game_init(t_game *game)
{
	game->mlx_ptr = NULL;
	game->mlx_win = NULL;
	map_init(&game->map);
	sprite_init_all(game);
	game->modified_cells = NULL;
	game->modified_cells_count = 0;
	game->window.height = 0;
	game->window.width = 0;
	game->window.y_start = 0;
	game->window.x_start = 0;
	game->window.y_end = 0;
	game->window.x_end = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->exit.x = 0;
	game->exit.y = 0;
	game->collectibles_count = 0;
	game->moves_count = 0;
}

void	game_free(t_game *game)
{
	if (game->modified_cells)
		free(game->modified_cells);
	map_free(&game->map);
	sprite_free_all(game);
	if (game->mlx_ptr)
	{
		if (game->mlx_win)
			mlx_destroy_window(game->mlx_ptr, game->mlx_win);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	game_init(game);
}
