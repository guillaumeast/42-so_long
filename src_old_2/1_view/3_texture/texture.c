#include "texture.h"
#include "fps.h"

# include <stdio.h>

t_texture	texture_new_static(t_sprite_set_id set_id, size_t image_id)
{
	t_texture	texture;

	texture.sprite_set = sprite_set_get(set_id);
	texture.image = texture.sprite_set.images[image_id];
	texture.image_index = 0;
	texture.frames_rendered = 0;
	texture.frames_total = 1;
	texture.frames_left = 1;
	texture.must_be_rendered = true;
	return (texture);
}

t_texture	texture_new_dynamic(t_sprite_set_id set_id, size_t duration_ms)
{
	t_texture	texture;

	texture.frames_total = (int)fps_ms_to_frames(duration_ms);
	if (texture.frames_total < 2)
		return (texture_new_static(set_id, 0));
	texture.sprite_set = sprite_set_get(set_id);
	texture.image_index = 0;
	texture.image = texture.sprite_set.images[0];
	texture.frames_rendered = 0;
	if (texture.frames_total < (int)texture.sprite_set.count)
		texture.frames_total = (int)texture.sprite_set.count;
	texture.frames_left = texture.frames_total;
	texture.must_be_rendered = true;
	return (texture);
}

void		texture_next(t_texture *texture)
{
	int	next_image_id;

	if (texture->frames_left > 0)
	{
		texture->frames_rendered++;
		texture->frames_left--;
	}
	if (texture->frames_left <= 0)
		return ;
	next_image_id = (texture->frames_rendered * ((int)texture->sprite_set.count - 1)) / (texture->frames_total - 1);
	texture->must_be_rendered = next_image_id == texture->image_index;
	texture->image_index = next_image_id;
	texture->image = texture->sprite_set.images[texture->image_index];
}

void	texture_print(t_texture *texture)
{
	fprintf(stderr, "🎨 h = %4ipx | w = %4ipx | image %i / %zu | frame %i / %i\n",
		texture->sprite_set.height, texture->sprite_set.width,
		texture->image_index + 1, texture->sprite_set.count,
		texture->frames_rendered, texture->frames_total);
}
