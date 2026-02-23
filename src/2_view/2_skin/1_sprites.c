#include "view_settings.h"
#include "view_mlx.h"
#include "view_skin.h"
#include "libft.h"
#include <stdlib.h>

static inline t_sprites	load_all_xpms(t_sprites sprites, char *path, size_t path_id_index);

t_sprites	sprites_load(
	const char *folder_path,
	t_size size,
	uint count)
{
	t_sprites	res;
	char	*path;
	size_t	path_id_index;

	res = (t_sprites){ 0 };
	path = str_join(folder_path, SPRITES_FILE_NAME);
	if (!path)
		return (fprint_err(true, "Unable to build skin path",
			" '%s" SPRITES_FILE_NAME "'", folder_path),
			(t_sprites){ 0 });
	path_id_index = str_len(folder_path) + 1;
	res.size = size;
	res.count = count;
	res = load_all_xpms(res, path, path_id_index);
	free(path);
	return (res);
}

static inline t_sprites	load_all_xpms(t_sprites sprites, char *path, size_t path_id_index)
{
	uint	i;

	sprites.images = malloc(sprites.count * sizeof * sprites.images);
	i = 0;
	while (i < sprites.count)
	{
		path[path_id_index] = 'A' + (char)i;
		sprites.images[i] = view_mlx_img_new(
			path, sprites.size.width, sprites.size.height);
		if (!sprites.images[i])
			return (sprites_free(sprites));
		i++;
	}
	return (sprites);
}

bool	sprites_check(t_sprites *sprites, uint count)
{
	uint	i;

	i = 0;
	while (i < count)
	{
		if (sprites[i++].images)
			continue ;
		fprint_err(false, "Invalid sprite", " %p[%u / %u]", sprites, i, count);
		sprites_free_all(sprites, count);
		return (false);
	}
	return (true);
}

void	sprites_free_all(t_sprites *sprites, uint count)
{
	uint	i;

	i = 0;
	while (i < count)
	{
		sprites[i] = sprites_free(sprites[i]);
		i++;
	}
}

t_sprites	sprites_free(t_sprites sprites)
{
	uint	i;

	if (!sprites.images)
		return ((t_sprites){ 0 });
	i = 0;
	while (i < sprites.count)
	{
		if (sprites.images[i])
			view_mlx_img_free(sprites.images[i]);
		i++;
	}
	free(sprites.images);
	return ((t_sprites){ 0 });
}
