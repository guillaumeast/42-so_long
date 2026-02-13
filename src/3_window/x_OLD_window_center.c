// #include "so_long.h"

// static inline void	center_y(t_game *game, int target_y);
// static inline void	center_x(t_game *game, int target_x);

// void	window_center(t_game *game, int target_y, int target_x)
// {
// 	if (!game->window.cropped)
// 		return ;
// 	center_y(game, target_y);
// 	center_x(game, target_x);
// }

// static inline void	center_y(t_game *game, int target_y)
// {
// 	if (game->window.y_start > target_y - PLAYER_PAD
// 		&& game->window.y_start > 0)
// 	{
// 		game->window.y_start--;
// 		game->window.y_end--;
// 		game->window.moved = true;
// 	}
// 	else if (game->window.y_end < target_y + PLAYER_PAD
// 		&& game->window.y_end < game->map.height - 1)
// 	{
// 		game->window.y_start++;
// 		game->window.y_end++;
// 		game->window.moved = true;
// 	}
// }

// static inline void	center_x(t_game *game, int target_x)
// {
// 	if (game->window.x_start > target_x - PLAYER_PAD
// 		&& game->window.x_start > 0)
// 	{
// 		game->window.x_start--;
// 		game->window.x_end--;
// 		game->window.moved = true;
// 	}
// 	else if (game->window.x_end < target_x + PLAYER_PAD
// 		&& game->window.x_end < game->map.width - 1)
// 	{
// 		game->window.x_start++;
// 		game->window.x_end++;
// 		game->window.moved = true;
// 	}
// }
