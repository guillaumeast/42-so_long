#include "so_long.h"
#include "render_priv.h"

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = game->window.y_start;
	while (y <= game->window.y_end)
	{
		x = game->window.x_start;
		while (x <= game->window.x_end)
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
	normalized_x = (x - game->window.x_start) * SPRITE_SIZE;
	normalized_y = (y - game->window.y_start) * SPRITE_SIZE + HUD_HEIGHT;
	render_image(game, game->sprites[cell], normalized_x, normalized_y);
}
