#include "mlx.h"
#include "so_long.h"

# include <stdio.h>

void	render_all(t_game *game)
{
	int	y;
	int	x;

	y = game->window.y_start;
	while (y <= game->window.y_end)
	{
		x = game->window.x_start;
		while (x <= game->window.x_end)
		{
			if (y == game->player.y && x == game->player.x)
				render_sprite(game, PLAYER, y, x);
			else if (game->map.grid[y][x] == '1')
				render_sprite(game, WALL, y, x);
			else if (game->map.grid[y][x] == 'C')
				render_sprite(game, COLLEC, y, x);
			else if (game->map.grid[y][x] == 'E')
				render_sprite(game, EXIT_CLOSE, y, x);
			else
				render_sprite(game, FLOOR, y, x);
			x++;
		}
		y++;
	}
}

void	render_sprite(t_game *game, t_sprite sprite, int y, int x)
{
	int	normalized_y;
	int	normalized_x;

	fprintf(stderr, "rendering cell y=%i | x=%i\n", y, x);
	if (sprite != FLOOR)
		render_sprite(game, FLOOR, y, x);
	if (sprite == EXIT_CLOSE && game->collectibles_count == 0)
		sprite = EXIT_OPEN;
	if (sprite == WALL && (y == 0 || y == game->map.height - 1))
		sprite = TOP_BOT;
	if (sprite == WALL && (x == 0 || x == game->map.width - 1))
		sprite = LEFT_RIGHT;
	y -= game->window.y_start;
	x -= game->window.x_start;
	normalized_y = y * SPRITE_SIZE;
	normalized_x = x * SPRITE_SIZE;
	mlx_put_image_to_window(
		game->mlx_ptr,
		game->mlx_win,
		game->sprites[sprite],
		normalized_x,
		normalized_y
	);
}
