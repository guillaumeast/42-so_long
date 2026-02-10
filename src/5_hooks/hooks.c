#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>

static inline void	move_player(t_game *game, int new_y, int new_x);
static inline void	update_player_sprite(t_game *game, int y, int x);
static inline void	decrement_collectibles(t_game *game);

int	handle_key_press(int event_data, void *param)
{
	static size_t	min_time_next_allowed = 0;
	static int		last_input;
	size_t			current_time;
	t_game			*game;

	game = (t_game *)param;
	current_time = get_time_in_ms(game);
	if (event_data == last_input && min_time_next_allowed > current_time)
		return (0);
	min_time_next_allowed = current_time + MIN_MS_BETWEEN_MOVES;
	last_input = event_data;
	if (event_data == KEY_UP)
		move_player(game, game->player.y - 1, game->player.x);
	else if (event_data == KEY_DOWN)
		move_player(game, game->player.y + 1, game->player.x);
	else if (event_data == KEY_LEFT)
		move_player(game, game->player.y, game->player.x - 1);
	else if (event_data == KEY_RIGHT)
		move_player(game, game->player.y, game->player.x + 1);
	else if (event_data == KEY_ESC)
		mlx_loop_end(game->mlx_ptr);
	return (0);
}

static inline void	move_player(t_game *game, int y, int x)
{
	int	cell;

	cell = (int)game->map.grid[y][x];
	if (cell <= WALL || cell == EXIT_CLOSE)
		return ;
	else if (cell == EXIT_OPEN)
		game_win(game);
	window_center(game, y, x);
	if (cell == COLLEC)
		decrement_collectibles(game);
	add_modified_cell(game, game->player.y, game->player.x);
	update_player_sprite(game, y, x);
	add_modified_cell(game, y, x);
	game->moves_count++;
	render_hud_update(game);
}

static inline void	update_player_sprite(t_game *game, int y, int x)
{
	if (game->map.grid[y][x] == COLLEC)
		game->map.grid[y][x] = PLAYER_COLLEC_2;
	else if (game->map.grid[y + 1][x] == COLLEC
		|| game->map.grid[y - 1][x] == COLLEC
		|| game->map.grid[y][x + 1] == COLLEC
		|| game->map.grid[y][x - 1] == COLLEC
	)
		game->map.grid[y][x] = PLAYER_COLLEC_1;
	else if (game->map.grid[game->player.y][game->player.x] == PLAYER_COLLEC_2)
		game->map.grid[y][x] = PLAYER_COLLEC_3;
	else
		game->map.grid[y][x] = PLAYER;
	game->map.grid[game->player.y][game->player.x] = FLOOR;
	game->player.y = y;
	game->player.x = x;
}

static inline void	decrement_collectibles(t_game *game)
{
	game->collectibles_count--;
	if (game->collectibles_count > 0)
		return ;
	game->map.grid[game->exit.y][game->exit.x] = EXIT_OPEN;
	add_modified_cell(game, game->exit.y, game->exit.x);
}

int	handle_window_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_end(game->mlx_ptr);
	return (0);
}
