#include "libft.h"
#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>

#define MIN_MS_BETWEEN_MOVES 50

static void	move_player(t_game *game, int new_y, int new_x);

int	handle_key_press(int event_data, void *param)
{
	static size_t	min_time_next_allowed = 0;
	size_t			current_time;
	t_game			*game;

	game = (t_game *)param;
	current_time = get_time_in_ms(game);
	if (min_time_next_allowed > current_time)
		return (0);
	min_time_next_allowed = current_time + MIN_MS_BETWEEN_MOVES;
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

static void	move_player(t_game *game, int new_y, int new_x)
{
	if (game->map.grid[new_y][new_x] == '1')
		return ;
	if (game->collectibles_count > 0 && game->map.grid[new_y][new_x] == 'E')
		return ;
	render_sprite(game, FLOOR, game->player.y, game->player.x);
	game->player.y = new_y;
	game->player.x = new_x;
	render_sprite(game, PLAYER, new_y, new_x);
	game->moves_count++;
	if (game->map.grid[game->player.y][game->player.x] == 'C')
	{
		game->map.grid[game->player.y][game->player.x] = '0';
		game->collectibles_count--;
		if (game->collectibles_count == 0)
			render_sprite(game, EXIT_OPEN, game->exit.y, game->exit.x);
	}
	if (game->collectibles_count == 0 && game->map.grid[new_y][new_x] == 'E')
		mlx_loop_end(game->mlx_ptr);
	window_center(game);
	if (game->window.moved)
		render_all(game);
	ft_printf("Moves = %i\n", (int)game->moves_count);
}

int handle_window_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_end(game->mlx_ptr);
	return (0);
}
