#include "libft.h"
#include "mlx.h"
#include "sprite_set_priv.h"
#include <stdlib.h>

# include "logs.h"

t_sprite_set	*sprite_set_init(void)
{
	t_sprite_set	*sets;
	t_sprite_set_id	id;

	sets = sprite_set_addr();
	id = 0;
	while (id < SPRITE_SET_COUNT)
	{
		sets[id].id = id;
		sets[id].images = NULL;
		sprite_set_init_dispatch(&sets[id]);
		id++;
	}
	return (sets);
}

bool	sprite_set_load(void *mlx_ptr)
{
	t_sprite_set	*sets;
	t_sprite_set_id	set_id;
	size_t			image_id;
	char			*path;

	sets = sprite_set_addr();
	path = str_dup(SPRITE_SET_PATH);
	if (!path)
		return (print_err(true, "Unable to dup path " SPRITE_SET_PATH), false);
	set_id = 0;
	while (set_id < SPRITE_SET_COUNT)
	{
		path[SPRITE_SET_ID_INDEX] = (char)(set_id + 'A');
		print_title("sprite_set '%c'...", path[SPRITE_SET_ID_INDEX]);
		sets[set_id].images = malloc(sets[set_id].count * sizeof(t_image));
		if (!sets[set_id].images)
			return (fprint_err(true, "Unable to malloc images", " of size %zu for sprite_set '%s'",
				sets[set_id].count * sizeof(t_image), path), free(path), false);
		image_id = 0;
		while (image_id < sets[set_id].count)
		{
			path[SPRITE_SET_FILE_INDEX] = (char)(image_id + 'A');
			if (!load_image(mlx_ptr, path, &sets[set_id], image_id))
				return (free(path), false);
			image_id++;
		}
		print_result("sprite_set '%c' loaded", path[SPRITE_SET_ID_INDEX]);
		set_id++;
	}
	return (free(path), true);
}

t_sprite_set	sprite_set_get(t_sprite_set_id sprite_set_id)
{
	t_sprite_set	*sets;

	sets = sprite_set_addr();
	return (sets[sprite_set_id]);
}

t_image	sprite_set_get_image(t_sprite_set_id sprite_set_id, size_t image_id)
{
	t_sprite_set	*sets;

	sets = sprite_set_addr();
	return (sets[sprite_set_id].images[image_id]);
}

void	sprite_set_free(void *mlx_ptr)
{
	t_sprite_set	*sets;
	t_sprite_set_id	set_id;
	size_t			image_id;

	sets = sprite_set_addr();
	set_id = 0;
	while (set_id < SPRITE_SET_COUNT)
	{
		if (mlx_ptr && sets[set_id].images)
		{
			image_id = 0;
			while (image_id < sets[set_id].count && sets[set_id].images[image_id])
			{
				mlx_destroy_image(mlx_ptr, sets[set_id].images[image_id]);
				sets[set_id].images[image_id] = NULL;
				image_id++;
			}
		}
		sprite_set_init_dispatch(&sets[set_id]);
		set_id++;
	}
}
