#include "mlx.h"
#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

static bool	sprite_load_letters(t_game *game);
static bool	sprite_load(void **sprites, t_sprite sprite, void *mlx_ptr);

bool	sprite_load_all(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < SPRITE_COUNT)
		if (!sprite_load(game->sprites, (t_sprite)i++, game->mlx_ptr))
			return (false);
	if (!sprite_load_letters(game))
		return (false);
	return (true);
}

static bool	sprite_load_letters(t_game *game)
{
	static char	path[19] = "sprites/font/X.xpm";
	int			width;
	int			height;
	int			i;

	i = 0;
	while (i < 26)
	{
		path[13] = (char)('A' + i);
		game->letters[i] = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
		if (!game->letters[i])
			return (fprint_err(true, "Sprite loading failed", " %s", path), false);
		if(width != LETTER_WIDTH || height != LETTER_HEIGHT)
			return (fprint_err(false, "Invalid sprite size", " '%s': width = %i x height = %i (expected %i x %i)", path, width, height, LETTER_WIDTH, LETTER_HEIGHT), false);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		path[13] = (char)('0' + i);
		game->numbers[i] = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
		if (!game->numbers[i])
			return (fprint_err(true, "Sprite loading failed", " %s", path), false);
		if(width != LETTER_WIDTH || height != LETTER_HEIGHT)
			return (fprint_err(false, "Invalid sprite size", " '%s': width = %i x height = %i (expected %i x %i)", path, width, height, LETTER_WIDTH, LETTER_HEIGHT), false);
		i++;
	}
	return (true);
}

static bool	sprite_load(void **sprites, t_sprite sprite, void *mlx_ptr)
{
	const char	*file;
	int			width;
	int			height;

	if (sprite == FLOOR)
		file = SPRITE_FLOOR;
	else if (sprite == WALL_TOP_BOT)
		file = SPRITE_TOP_BOT;
	else if (sprite == WALL_LEFT_RIGHT)
		file = SPRITE_LEFT_RIGHT;
	else if (sprite == WALL)
		file = SPRITE_WALL;
	else if (sprite == COLLEC)
		file = SPRITE_COLLEC;
	else if (sprite == EXIT_CLOSE)
		file = SPRITE_EXIT_CLOSE;
	else if (sprite == EXIT_OPEN)
		file = SPRITE_EXIT_OPEN;
	else if (sprite == PLAYER)
		file = SPRITE_PLAYER;
	else if (sprite == HUD_BACKGROUND)
		file = SPRITE_HUD_BACKGROUND;
	else
		return (false);
	sprites[sprite] = mlx_xpm_file_to_image(mlx_ptr, (char *)file, &width, &height);
	if (!sprites[sprite])
		return (fprint_err(true, "Sprite loading failed", " %s", file), false);
	if(sprite != HUD_BACKGROUND && (width != SPRITE_SIZE || height != SPRITE_SIZE))
		return (fprint_err(false, "Invalid sprite size", " '%s': width = %i x height = %i (expected %i x %i)", file, width, height, SPRITE_SIZE, SPRITE_SIZE), false);
	return (true);
}
