#include "view_skin.h"
#include <stdlib.h>

t_skin	skin_load(const char *folder_path, t_size size, uint count, uint ms)
{
	return ((t_skin)
		{
			.sprites = sprites_load(folder_path, size, count),
			.ms_anim = ms,
			.own_array = true,
			.own_imgs = true
		});
}

bool	skin_check_all(t_skin *skins, uint count)
{
	uint	i;

	i = 0;
	while (i < count)
		if (!skins[i++].own_imgs)
			return (skin_free_all(skins, count), false);
	return (true);
}

t_skin	skin_dup(t_skin skin)
{
	skin.own_imgs = false;
	skin.own_array = false;
	return (skin);
}

t_skin	skin_join(t_skin skin_1, t_skin skin_2)
{
	t_img	*new_imgs;
	uint	i;
	uint	j;

	new_imgs = malloc((skin_1.sprites.count + skin_2.sprites.count) * sizeof * new_imgs);
	if (!new_imgs)
		return (skin_1);
	i = 0;
	while (i < skin_1.sprites.count)
	{
		new_imgs[i] = skin_1.sprites.images[i];
		i++;
	}
	j = 0;
	while (j < skin_2.sprites.count)
	{
		new_imgs[i] = skin_2.sprites.images[j];
		i++;
		j++;
	}
	skin_1.sprites.images = new_imgs;
	skin_1.sprites.count += skin_2.sprites.count;
	skin_1.own_array = true;
	skin_1.own_imgs = false;
	return (skin_1);
}

t_skin	skin_new_static(t_skin skin)
{
	return ((t_skin)
		{
			.sprites.images = skin.sprites.images,
			.sprites.size = skin.sprites.size,
			.sprites.count = 1,
			.ms_anim = 0,
			.own_array = false,
			.own_imgs = false
		});
}

t_skin	skin_new_anim(t_skin skin, uint ms)
{
	return ((t_skin)
		{
			.sprites = skin.sprites,
			.ms_anim = ms,
			.own_array = false,
			.own_imgs = false
		});
}

// Returns initial skin on failure
t_skin	skin_new_custom(t_skin skin, uint start_id, uint end_id, uint ms)
{
	t_skin	reversed;
	uint	i;
	uint	j;

	skin.own_array = false;
	skin.own_imgs = false;
	if (start_id <= end_id)
	{
		skin.sprites.images += start_id;
		skin.sprites.count = (end_id - start_id) + 1;
		skin.ms_anim = ms;
		return (skin);
	}
	reversed = skin;
	reversed.sprites.count = (start_id - end_id) + 1;
	reversed.sprites.images = malloc(reversed.sprites.count * sizeof * reversed.sprites.images);
	if (!reversed.sprites.images)
		return (skin);
	reversed.own_array = true;
	i = 0;
	j = start_id;
	while (j >= end_id)
		reversed.sprites.images[i++] = skin.sprites.images[j--];
	return (reversed);
}

// Returns initial skin on failure
t_skin	skin_new_reversed(t_skin src)
{
	return (skin_new_custom(src, src.sprites.count - 1, 0, src.ms_anim));
}

t_skin	skin_free(t_skin skin)
{
	if (skin.own_imgs)
		(void)sprites_free(skin.sprites);
	else if (skin.own_array)
		free(skin.sprites.images);
	return ((t_skin){ 0 });
}

void	skin_free_all(t_skin *skins, uint count)
{
	uint	i;

	i = 0;
	while (i < count)
	{
		skins[i] = skin_free(skins[i]);
		i++;
	}
}
