#include "libft.h"
#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>

static void	move_player(t_game *game, size_t new_y, size_t new_x);

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
		mlx_loop_end(game->context);
	return (0);
}

static void	move_player(t_game *game, size_t new_y, size_t new_x)
{
	t_object	*player;

	if (game->map.grid[new_y][new_x] == '1')
		return ;
	if (game->collectibles_count > 0 && game->map.grid[new_y][new_x] == 'E')
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
		game->collectibles_count--;
		if (game->collectibles_count == 0)
		{
			render_sprite(game, FLOOR, game->exit.y, game->exit.x);
			render_sprite(game, EXIT_OPEN, game->exit.y, game->exit.x);
		}
	}
	if (game->collectibles_count == 0 && game->map.grid[new_y][new_x] == 'E')
		mlx_loop_end(game->context);
	ft_printf("Moves = %i\n", (int)game->moves_count);
}

int handle_window_close(int event_data, void *param)
{
	t_game	*game;
	// size_t	i;

	(void)event_data;
	game = (t_game *)param;
	print_result("window closed");
	if (game->map.grid)
		str_array_free(&game->map.grid);
	// if (game->context)
	// {
	// 	i = 0;
	// 	while (i < SPRITE_COUNT && game->sprites[i])
	// 	{
	// 		mlx_destroy_image(game->context, game->sprites[i]);
	// 		i++;
	// 	}
	// 	if (game->window)
	// 		mlx_destroy_window(game->context, game->window);
	// 	mlx_destroy_display(game->context);
	// }
	// free(game->context);
	exit(EXIT_SUCCESS);
}
