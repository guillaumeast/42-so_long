#include "libft.h"
#include "mlx.h"
#include "sprite_set.h"
#include <stdlib.h>

# include "logs.h"

static bool	sprite_set_init(t_sprite_set *sprite_set);
static inline bool	load_image(
	void *mlx_ptr,
	char *path,
	t_sprite_set *sprite_set,
	size_t index);

void	sprite_set_init_all(t_sprite_set (*sprite_sets)[SPRITE_SET_COUNT])
{
	t_sprite_set_id	sprite_set_id;

	sprite_set_id = 0;
	while (sprite_set_id < SPRITE_SET_COUNT)
	{
		(*sprite_sets)[sprite_set_id].id = sprite_set_id;
		(*sprite_sets)[sprite_set_id].images = NULL;
		sprite_set_init(&(*sprite_sets)[sprite_set_id]);
		sprite_set_id++;
	}
}

static bool	sprite_set_init(t_sprite_set *sprite_set)
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
	else
		return (false);
	return (true);
}

bool	sprite_set_load_all(void *mlx_ptr, t_sprite_set (*sprite_sets)[SPRITE_SET_COUNT])
{
	size_t	sprite_set;
	size_t	sprite;
	char	*path;

	path = str_dup(SPRITE_SET_PATH);
	if (!path)
		return (print_err(true, "Unable to dup path " SPRITE_SET_PATH), false);
	sprite_set = 0;
	while (sprite_set < SPRITE_SET_COUNT)
	{
		path[SPRITE_SET_ID_INDEX] = (char)(sprite_set + 'A');
		print_title("sprite_set '%c'...", path[SPRITE_SET_ID_INDEX]);
		(*sprite_sets)[sprite_set].images = malloc((*sprite_sets)[sprite_set].count * sizeof(t_image));
		if (!(*sprite_sets)[sprite_set].images)
			return (fprint_err(true, "Unable to malloc images", " of size %zu for sprite_set '%s'",
				(*sprite_sets)[sprite_set].count * sizeof(t_image), path), free(path), false);
		sprite = 0;
		while (sprite < (*sprite_sets)[sprite_set].count)
		{
			path[SPRITE_SET_FILE_INDEX] = (char)(sprite + 'A');
			if (!load_image(mlx_ptr, path, &(*sprite_sets)[sprite_set], sprite))
				return (free(path), false);
			sprite++;
		}
		print_result("sprite_set '%c' loaded", path[SPRITE_SET_ID_INDEX]);
		sprite_set++;
	}
	return (free(path), true);
}

void	sprite_set_free_all(void *mlx_ptr, t_sprite_set (*sprite_sets)[SPRITE_SET_COUNT])
{
	t_sprite_set_id	sprite_set;
	size_t			image;

	sprite_set = 0;
	while (sprite_set < SPRITE_SET_COUNT)
	{
		if (mlx_ptr && (*sprite_sets)[sprite_set].images)
		{
			image = 0;
			while (image < (*sprite_sets)[sprite_set].count && (*sprite_sets)[sprite_set].images[image])
			{
				mlx_destroy_image(mlx_ptr, (*sprite_sets)[sprite_set].images[image]);
				(*sprite_sets)[sprite_set].images[image] = NULL;
				image++;
			}
		}
		sprite_set_init(&(*sprite_sets)[sprite_set]);
		sprite_set++;
	}
}

static inline bool	load_image(
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
