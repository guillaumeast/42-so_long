#include "mlx.h"
#include "libft.h"
#include "so_long.h"

# include <stdio.h>

void	render_all(t_game *game)
{
	int	y;
	int	x;

	render_string(game, "DAYS IN JAIL", HUD_Y_PADDING);
	render_number(game, 0, HUD_Y_PADDING, HUD_X_PADDING + HUD_TITLE_LEN * LETTER_WIDTH);
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

void	render_hud_background(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->window.width)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->sprites[HUD_BACKGROUND], i, 0);
		i++;
	}
}

void	render_string(t_game *game, const char *string, size_t x)
{
	size_t	i;
	size_t	len;
	int		index;

	len = str_len(string);
	i = 0;
	while (i < len)
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
		{
			index = string[i] - 'A';
			mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->letters[index], (int)(x + LETTER_WIDTH * i), HUD_Y_PADDING);
		}
		if (string[i] >= '0' && string[i] <= '9')
		{
			index = string[i] - '0';
			mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->numbers[index], (int)(x + LETTER_WIDTH * i), HUD_Y_PADDING);
		}
		i++;
	}
}

void	render_number(t_game *game, size_t number, int y, int x)
{
	size_t	number_copy;

	if (number == 0)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->numbers[0], x, y);
		return ;
	}
	number_copy = number;
	while (number_copy / 10 > 0)
	{
		number_copy /= 10;
		x += LETTER_WIDTH;
	}
	while (number / 10 > 0)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->numbers[number % 10], x, y);
		number /= 10;
		x -= LETTER_WIDTH;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->numbers[number], x, y);
}

void	render_sprite(t_game *game, t_sprite sprite, int y, int x)
{
	int	normalized_y;
	int	normalized_x;

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
	normalized_y = HUD_HEIGHT + y * SPRITE_SIZE;
	normalized_x = x * SPRITE_SIZE;
	mlx_put_image_to_window(
		game->mlx_ptr,
		game->mlx_win,
		game->sprites[sprite],
		normalized_x,
		normalized_y
	);
}
