#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

static void	move_player(t_game *game, size_t new_y, size_t new_x);
static void	update_exit_sprite(t_game *game);

int	handle_key_press(int event_data, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (event_data == KEY_UP)
		move_player(game, game->player.y - 1, game->player.x);
	else if (event_data == KEY_DOWN)
		move_player(game, game->player.y + 1, game->player.x);
	else if (event_data == KEY_LEFT)
		move_player(game, game->player.y, game->player.x - 1);
	else if (event_data == KEY_RIGHT)
		move_player(game, game->player.y, game->player.x + 1);
	else if (event_data == KEY_ESC)
		game_free(game);	// TODO: mlx_loop_end() askip ça existe sur Linux...
	return (0);
}

// TODO: win if exit and collectibles = 0
static void	move_player(t_game *game, size_t new_y, size_t new_x)
{
	t_object	*player;

	if (game->map.grid[new_y][new_x] == '1')
		return ;
	if (game->map.collectibles > 0 && game->map.grid[new_y][new_x] == 'E')
		return ;
	render_sprite(game, FLOOR, game->player.y, game->player.x);
	player = &game->player;
	player->y = new_y;
	player->x = new_x;
	render_sprite(game, FLOOR, new_y, new_x);
	render_sprite(game, PLAYER, new_y, new_x);
	game->moves_count++;
	if (game->map.grid[game->player.y][game->player.x] == 'C')
	{
		game->map.grid[game->player.y][game->player.x] = '0';
		game->map.collectibles--;
		if (game->map.collectibles == 0)
			update_exit_sprite(game);
	}
	if (game->map.collectibles == 0 && game->map.grid[new_y][new_x] == 'E')
	{
		// TODO: Uncomment before submit (only available in Linux mlx)
		// mlx_loop_end(game->context)
		game_free(game);
	}
	ft_printf("Moves = %i\n", (int)game->moves_count);
}

// TODO: add exit object to game struct to find it in 0(1)
static void	update_exit_sprite(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 1;
	while (y < game->map.height - 1)
	{
		x = 1;
		while (x < game->map.width - 1)
		{
			if (game->map.grid[y][x] == 'E')
			{
				render_sprite(game, FLOOR, y, x);
				render_sprite(game, EXIT_OPEN, y, x);
				return ;
			}
			x++;
		}
		y++;
	}
}

int handle_window_close(int event_data, void *param)
{
	(void)event_data;
	(void)param;
	// TODO: SEGV quand call game_free() ici, selon chatGPT c'est normal, il suffit d'exit....
	exit(EXIT_SUCCESS);
}
