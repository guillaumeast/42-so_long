#include "mlx.h"
#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

static bool	sprite_load(void **sprites, t_sprite sprite, void *mlx_ptr);

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

bool	sprite_load_all(void **sprites, void *mlx_ptr)
{
	if (!sprite_load(sprites, FLOOR, mlx_ptr)
		|| !sprite_load(sprites, TOP_BOT, mlx_ptr)
		|| !sprite_load(sprites, LEFT_RIGHT, mlx_ptr)
		|| !sprite_load(sprites, WALL, mlx_ptr)
		|| !sprite_load(sprites, COLLEC, mlx_ptr)
		|| !sprite_load(sprites, EXIT_CLOSE, mlx_ptr)
		|| !sprite_load(sprites, EXIT_OPEN, mlx_ptr)
		|| !sprite_load(sprites, PLAYER, mlx_ptr)
	)
		return (sprite_free_all(sprites, mlx_ptr), false);
	return (true);
}

static bool	sprite_load(void **sprites, t_sprite sprite, void *mlx_ptr)
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
	sprites[sprite] = mlx_xpm_file_to_image(mlx_ptr, (char *)file, &width, &height);
	if (!sprites[sprite])
		return (fprint_err(true, "Sprite loading failed", " %s", file), false);
	if(width != SPRITE_SIZE || height != SPRITE_SIZE)
		return (fprint_err(false, "Invalid sprite size",
			" '%s': width = %i x height = %i (expected %i x %i)",
			file, width, height, SPRITE_SIZE, SPRITE_SIZE), false);
	return (true);
}

void	sprite_free_all(void **sprites, void *mlx_ptr)
{
	size_t	i;

	if (!sprites || !mlx_ptr)
		return ;
	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (sprites[i])
			mlx_destroy_image(mlx_ptr, sprites[i]);
		i++;
	}
}
