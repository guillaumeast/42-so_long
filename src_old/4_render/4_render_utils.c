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

	chars = game->sprites.letters;
	nums = game->sprites.numbers;
	i = 0;
	while (i < string[i])
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
		{
			index = string[i] - 'A';
			render_image(game, chars[index], x + SPRITES_FONT_WIDTH_PX * i, WINDOW_IN_PAD_PX);
		}
		if (string[i] >= '0' && string[i] <= '9')
		{
			index = string[i] - '0';
			render_image(game, nums[index], x + SPRITES_FONT_WIDTH_PX * i, WINDOW_IN_PAD_PX);
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
	render_image(game, game->sprites.numbers[number % 10], x, y);
	return (x + SPRITES_FONT_WIDTH_PX);
}

void	render_image(t_game *game, void *image, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->window.mlx_win, image, x, y);
}
