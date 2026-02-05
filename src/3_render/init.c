#include "mlx.h"
#include "so_long.h"

static void	add_floor(t_game *game);
static void	add_borders(t_game *game);

void	render_init(t_game *game)
{
	size_t	y;
	size_t	x;

	print_title("render_init()");
	add_floor(game);
	print_pass("floor added\n");
	add_borders(game);
	print_pass("borders added\n");
	y = 1;
	while (y < game->map.height - 1)
	{
		x = 1;
		while (x < game->map.width - 1)
		{
			if (y == game->player.y && x == game->player.x)
				render_sprite(game, PLAYER, game->player.y, game->player.x);
			else if (game->map.grid[y][x] == '1')
				render_sprite(game, WALL, y, x);
			else if (game->map.grid[y][x] == 'C')
				render_sprite(game, COLLEC, y, x);
			else if (game->map.grid[y][x] == 'E')
				render_sprite(game, EXIT_CLOSE, y, x);
			x++;
		}
		y++;
	}
	print_result("render inited");
}

static void	add_floor(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_sprite(game, FLOOR, y, x);
			x++;
		}
		y++;
	}
}

static void	add_borders(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.width)
	{
		render_sprite(game, TOP_BOT, 0, i);
		render_sprite(game, TOP_BOT, game->map.height - 1, i);
		i++;
	}
	i = 1;
	while (i < game->map.height - 1)
	{
		render_sprite(game, LEFT_RIGHT, i, 0);
		render_sprite(game, LEFT_RIGHT, i, game->map.width -1);
		i++;
	}
}

void	render_sprite(t_game *game, t_sprite sprite, size_t y, size_t x)
{
	size_t	normed_y;
	size_t	normed_x;

	normed_y = y * SPRITE_SIZE;
	normed_x = x * SPRITE_SIZE;
	mlx_put_image_to_window(game->context, game->window, game->sprites[sprite],
		(int)normed_x, (int)normed_y);
}
