// #include "libft.h"
// #include "mlx.h"
// #include "so_long.h"

// static void	window_crop(t_game *game, int display_height, int display_width);
// static void	window_init_center(t_game *game);

// bool	window_init(t_game *game)
// {
// 	int	display_height;
// 	int	display_width;

// 	mlx_get_screen_size(game->mlx_ptr, &display_width, &display_height);
// 	if (display_height < 0 || display_width < 0)
// 	{
// 		print_err(false, "mlx_get_screen_size() returned negative values");
// 		return (false);
// 	}
// 	window_crop(game, display_height, display_width);
// 	if (game->window.cropped)
// 		window_init_center(game);
// 	game->mlx_win = mlx_new_window(
// 		game->mlx_ptr,
// 		(int)game->window.width,
// 		(int)game->window.height,
// 		(char *)"so_long"
// 	);
// 	if (!game->mlx_win)
// 		return (print_err(true, "mlx_new_window() failed"), false);
// 	return (true);
// }

// static void	window_crop(t_game *game, int display_height, int display_width)
// {
// 	game->window.height = SPRITE_SIZE * game->map.height + HUD_HEIGHT;
// 	game->window.width = SPRITE_SIZE * game->map.width;
// 	game->window.y_start = 0;
// 	game->window.x_start = 0;
// 	game->window.y_end = game->map.height - 1;
// 	game->window.x_end = game->map.width - 1;
// 	game->window.cropped = false;
// 	while (game->window.height > display_height - WINDOW_PAD)
// 	{
// 		game->window.y_end--;
// 		game->window.height -= SPRITE_SIZE;
// 		game->window.cropped = true;
// 	}
// 	while (game->window.width > display_width - WINDOW_PAD)
// 	{
// 		game->window.x_end--;
// 		game->window.width -= SPRITE_SIZE;
// 		game->window.cropped = true;
// 	}
// }

// static void	window_init_center(t_game *game)
// {
// 	while (game->window.y_end < game->player.y + PLAYER_PAD
// 		&& game->window.y_end < game->map.height - 1)
// 	{
// 		game->window.y_start++;
// 		game->window.y_end++;
// 	}
// 	while (game->window.x_end < game->player.x + PLAYER_PAD
// 		&& game->window.x_end < game->map.width - 1)
// 	{
// 		game->window.x_start++;
// 		game->window.x_end++;
// 	}
// }
