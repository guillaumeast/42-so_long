#include "mlx.h"
#include "so_long.h"
#include "render_priv.h"

static int	render_number_rec(t_game *game, size_t number, int y, int x);

void	render_string(t_game *game, const char *string, int x)
{
	int		i;
	int		index;
	void	**chars;
	void	**nums;

	chars = game->letters;
	nums = game->numbers;
	i = 0;
	while (i < string[i])
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
		{
			index = string[i] - 'A';
			render_image(game, chars[index], x + LETTER_WIDTH * i, HUD_Y_PAD);
		}
		if (string[i] >= '0' && string[i] <= '9')
		{
			index = string[i] - '0';
			render_image(game, nums[index], x + LETTER_WIDTH * i, HUD_Y_PAD);
		}
		i++;
	}
}

void	render_number(t_game *game, size_t number, int y, int x)
{
	render_number_rec(game, number, y, x);
}

static int	render_number_rec(t_game *game, size_t number, int y, int x)
{
	if (number >= 10)
		x = render_number_rec(game, number / 10, y, x);
	render_image(game, game->numbers[number % 10], x, y);
	return (x + LETTER_WIDTH);
}

void	render_image(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, image, x, y);
}
