#include "mlx.h"
#include "so_long.h"

void	sprite_init_all(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		game->sprites[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 26)
	{
		game->letters[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 10)
	{
		game->numbers[i] = NULL;
		i++;
	}
}

void	sprite_free_all(t_game *game)
{
	size_t	i;

	if (!game->mlx_ptr)
		return ;
	i = 0;
	while (i < SPRITE_COUNT && game->sprites[i])
	{
		mlx_destroy_image(game->mlx_ptr, game->sprites[i]);
		game->sprites[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 26 && game->letters[i])
	{
		mlx_destroy_image(game->mlx_ptr, game->letters[i]);
		game->letters[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 10 && game->numbers[i])
	{
		mlx_destroy_image(game->mlx_ptr, game->numbers[i]);
		game->numbers[i] = NULL;
		i++;
	}
}
