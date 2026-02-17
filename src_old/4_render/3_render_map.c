#include "so_long.h"
#include "render_priv.h"

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = game->window.map_y_cell_start;
	while (y <= game->window.map_y_cell_end)
	{
		x = game->window.map_x_cell_start;
		while (x <= game->window.map_x_cell_end)
		{
			render_cell(game, y, x);
			x++;
		}
		y++;
	}
	game->window.moved = false;
}

void	render_cell(t_game *game, int y, int x)
{
	int	normalized_x;
	int	normalized_y;
	int	cell;

	cell = (int)game->map.grid[y][x];
	normalized_x = (x - game->window.map_x_cell_start) * SPRITES_MAP_WIDTH_PX;
	normalized_x += game->window.map_x_pos_px;
	normalized_y = (y - game->window.map_y_cell_start) * SPRITES_MAP_HEIGHT_PX;
	normalized_y += game->window.map_y_pos_px;
	render_image(game, game->sprites.map[cell], normalized_x, normalized_y);
}
