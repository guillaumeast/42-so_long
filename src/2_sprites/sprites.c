#include "mlx.h"
#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

static bool	sprite_load(void **sprites, t_sprite sprite, void *context);

void	sprite_init_all(void **sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		sprites[i] = NULL;
		i++;
	}
}

bool	sprite_load_all(void **sprites, void *context)
{
	if (!sprite_load(sprites, FLOOR, context)
		|| !sprite_load(sprites, TOP_BOT, context)
		|| !sprite_load(sprites, LEFT_RIGHT, context)
		|| !sprite_load(sprites, WALL, context)
		|| !sprite_load(sprites, COLLEC, context)
		|| !sprite_load(sprites, EXIT_CLOSE, context)
		|| !sprite_load(sprites, EXIT_OPEN, context)
		|| !sprite_load(sprites, PLAYER, context)
	)
		return (sprite_free_all(sprites, context), false);
	return (true);
}

static bool	sprite_load(void **sprites, t_sprite sprite, void *context)
{
	const char	*file;
	int			width;
	int			height;

	if (sprite == FLOOR)
		file = SPRITE_FLOOR;
	else if (sprite == TOP_BOT)
		file = SPRITE_TOP_BOT;
	else if (sprite == LEFT_RIGHT)
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
	else
		return (false);
	sprites[sprite] = mlx_xpm_file_to_image(context, (char *)file, &width, &height);
	if (!sprites[sprite])
		return (fprint_err(true, "Sprite loading failed", " %s", file), false);
	if(width != SPRITE_SIZE || height != SPRITE_SIZE)
		return (fprint_err(false, "Invalid sprite size",
			" '%s': width = %i x height = %i (expected %i x %i)",
			file, width, height, SPRITE_SIZE, SPRITE_SIZE), false);
	return (true);
}

void	sprite_free_all(void **sprites, void *context)
{
	size_t	i;

	if (!sprites || !context)
		return ;
	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (sprites[i])
			mlx_destroy_image(context, sprites[i]);
		i++;
	}
}
