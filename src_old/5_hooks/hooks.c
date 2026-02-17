#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>

// static inline void	move_player(t_game *game, int new_y, int new_x);
// static inline void	decrement_collectibles(t_game *game);

int	handle_key_press(int event_data, void *param)
{
	(void)event_data;
	(void)param;
	// static size_t	min_time_next_allowed = 0;
	// static int		last_input;
	// size_t			current_time;
	// t_game			*game;

	// game = (t_game *)param;
	// current_time = get_time_in_ms(game);
	// if (event_data == last_input && min_time_next_allowed > current_time)
	// 	return (0);
	// min_time_next_allowed = current_time + MIN_MS_BETWEEN_MOVES;
	// last_input = event_data;
	// if (event_data == KEY_UP)
	// 	move_player(game, game->map.player.y - 1, game->map.player.x);
	// else if (event_data == KEY_DOWN)
	// 	move_player(game, game->map.player.y + 1, game->map.player.x);
	// else if (event_data == KEY_LEFT)
	// 	move_player(game, game->map.player.y, game->map.player.x - 1);
	// else if (event_data == KEY_RIGHT)
	// 	move_player(game, game->map.player.y, game->map.player.x + 1);
	// else if (event_data == KEY_ESC)
	// 	mlx_loop_end(game->mlx_ptr);
	return (0);
}

// static inline void	move_player(t_game *game, int y, int x)
// {
// 	int	cell;

// 	cell = (int)game->map.grid[y][x];
// 	if (cell <= SPRITES_WALL || cell == SPRITES_EXIT_CLOSE)
// 		return ;
// 	else if (cell == SPRITES_EXIT_OPEN)
// 		game_win(game);
// 	if (cell == SPRITES_COLLEC)
// 		decrement_collectibles(game);
// 	add_modified_cell(game, game->map.player.y, game->map.player.x);
// 	add_modified_cell(game, y, x);
// 	game->moves_count++;
// }

// static inline void	decrement_collectibles(t_game *game)
// {
// 	game->map.collectibles_count--;
// 	if (game->map.collectibles_count > 0)
// 		return ;
// 	game->map.grid[game->map.exit.y][game->map.exit.x] = SPRITES_EXIT_OPEN;
// 	add_modified_cell(game, game->map.exit.y, game->map.exit.x);
// }

int	handle_window_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_end(game->mlx_ptr);
	return (0);
}
