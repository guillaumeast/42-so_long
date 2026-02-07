#include "libft.h"
#include "mlx.h"
#include "so_long.h"

# include <stdio.h>
#include <stdlib.h>

#define WINDOW_PADDING	100
#define PLAYER_PADDING	2

static void	window_crop(t_game *game, int display_height, int display_width);
static void	center_y(t_game *game);
static void	center_x(t_game *game);

bool	window_init(t_game *game)
{
	int	display_height;
	int	display_width;

	mlx_get_screen_size(game->mlx_ptr, &display_width, &display_height);
	if (display_height < 0 || display_width < 0)
	{
		print_err(false, "mlx_get_screen_size() returned negative values");
		return (false);
	}
	window_crop(game, display_height, display_width);
	game->mlx_win = mlx_new_window(
		game->mlx_ptr,
		(int)game->window.width,
		(int)game->window.height,
		(char *)"so_long"
	);
	window_center(game);
	render_hud_background(game);
	render_all(game);
	game->window.moved = false;
	if (!game->mlx_win)
		return (print_err(true, "Window init failed"), false);
	return (true);
}

static void	window_crop(t_game *game, int display_height, int display_width)
{
	game->window.height = SPRITE_SIZE * game->map.height + HUD_HEIGHT;
	game->window.width = SPRITE_SIZE * game->map.width;
	game->window.y_start = 0;
	game->window.x_start = 0;
	game->window.y_end = game->map.height - 1;
	game->window.x_end = game->map.width - 1;
	if (game->window.height <= display_height - WINDOW_PADDING && game->window.width <= display_width - WINDOW_PADDING)
	{
		game->window.cropped = false;
		return ;
	}
	game->window.cropped = true;
	while (game->window.height > display_height - WINDOW_PADDING)
	{
		game->window.y_end--;
		game->window.height -= SPRITE_SIZE;
	}
	while (game->window.width > display_width - WINDOW_PADDING)
	{
		game->window.x_end--;
		game->window.width -= SPRITE_SIZE;
	}
}

void	window_center(t_game *game)
{
	if (!game->window.cropped)
		return ;
	center_y(game);
	center_x(game);
}

static void	center_y(t_game *game)
{
	while (game->window.y_start + PLAYER_PADDING > game->player.y && game->window.y_start > 0)
	{
		game->window.y_start--;
		game->window.y_end--;
		game->window.moved = true;
	}
	while (game->window.y_end - PLAYER_PADDING < game->player.y && game->window.y_end < game->map.height - 1)
	{
		game->window.y_start++;
		game->window.y_end++;
		game->window.moved = true;
	}
}

static void	center_x(t_game *game)
{
	while (game->window.x_start + PLAYER_PADDING > game->player.x && game->window.x_start > 0)
	{
		game->window.x_start--;
		game->window.x_end--;
		game->window.moved = true;
	}
	while (game->window.x_end - PLAYER_PADDING < game->player.x && game->window.x_end < game->map.width - 1)
	{
		game->window.x_start++;
		game->window.x_end++;
		game->window.moved = true;
	}
}
