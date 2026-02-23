#include "libft.h"
#include "mlx.h"
#include "sprite_set.h"
#include <stdlib.h>

# include "logs.h"

t_sprite_set	*sprite_set_addr(void)
{
	static t_sprite_set	sprite_sets[SPRITE_SET_COUNT];

	return (sprite_sets);
}

bool	sprite_set_init_dispatch(t_sprite_set *sprite_set)
{
	if (sprite_set->id == SPRITE_SET_HUD_BACKGROUND)
	{
		sprite_set->height = SPRITE_SET_HUD_BACKGROUND_HEIGHT_PX;
		sprite_set->width = SPRITE_SET_HUD_BACKGROUND_WIDTH_PX;
		sprite_set->count = SPRITE_HUD_BACKGROUND_COUNT;
	}
	else if (sprite_set->id == SPRITE_SET_HUD_LOADING)
	{
		sprite_set->height = SPRITE_SET_HUD_LOADING_HEIGHT_PX;
		sprite_set->width = SPRITE_SET_HUD_LOADING_WIDTH_PX;
		sprite_set->count = SPRITE_HUD_LOADING_COUNT;
	}
	else if (sprite_set->id == SPRITE_SET_XAV)
	{
		sprite_set->height = SPRITE_SET_XAV_FULL_HEIGHT_PX;
		sprite_set->width = SPRITE_SET_XAV_FULL_WIDTH_PX;
		sprite_set->count = SPRITE_XAV_COUNT;
	}
	else
		return (false);
	return (true);
}

bool	load_image(
	void *mlx_ptr,
	char *path,
	t_sprite_set *sprite_set,
	size_t sprite_index)
{
	int		height;
	int		width;

	sprite_set->images[sprite_index] = mlx_xpm_file_to_image(
		mlx_ptr, path, &width, &height);
	if (!sprite_set->images[sprite_index])
	{
		fprint_err(true,
			"Unable to load sprite", " %s", path);
		return (false);
	}
	if (width != sprite_set->width && height != sprite_set->height)
	{
		fprint_err(false,
			"Invalid sprite size",
			" '%s': width = %i x height = %i (expected %i x %i)",
			path, width, height,
			sprite_set->width, sprite_set->height);
		return (false);
	}
	print_pass("image '%s' loaded\n", path);
	return (true);
}
