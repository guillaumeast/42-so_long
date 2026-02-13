#include "mlx.h"
#include "libft.h"
#include "sprites_priv.h"
#include <stdlib.h>

bool	sprites_load_array(void *mlx_ptr, t_sprite_array *sprite_array)
{
	size_t		i;
	t_sprite	sprite;

	sprite.path = str_dup(sprite_array->base_path);
	if (!sprite.path)
	{
		fprint_err(true, "Sprite loading failed", " %s", sprite_array->base_path);
		return (false);
	}
	sprite.expected_height = sprite_array->expected_height;
	sprite.expected_width = sprite_array->expected_width;
	i = 0;
	while (i < sprite_array->count)
	{
		sprite.path[sprite_array->path_id_index] = (char)(i + 'A');
		if (!sprites_load(mlx_ptr, &sprite, &sprite_array->dst_array[i]))
			return (false);
		i++;
	}
	free(sprite.path);
	return (true);
}

bool	sprites_load(void *mlx_ptr, t_sprite *sprite, t_image *dst)
{
	int	height;
	int	width;

	*dst = mlx_xpm_file_to_image(mlx_ptr, sprite->path, &width, &height);
	if (!*dst)
	{
		fprint_err(true, "Sprite loading failed", " %s", sprite->path);
		return (false);
	}
	if (width != sprite->expected_width || height != sprite->expected_height)
	{
		fprint_err(false,
			"Invalid sprite size",
			" '%s': width = %i x height = %i (expected %i x %i)",
			sprite->path, width, height,
			sprite->expected_width, sprite->expected_height
		);
		sprites_free(mlx_ptr, dst);
		return (false);
	}
	return (true);
}

void	sprites_free(void *mlx_ptr, t_image *image)
{
	if (!image || !*image)
		return ;
	mlx_destroy_image(mlx_ptr, *image);
	*image = NULL;
}
