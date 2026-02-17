#include "texture.h"
#include "fps.h"

t_texture	texture_new_static(t_image image)
{
	return ((t_texture)
		{
			.image = image,
			.images_left = 0,
			.frames_left = 1
		});
}

t_texture	texture_new_dynamic(t_sprite_set sprite_set, int duration_ms)
{
	t_texture	texture;

	if (duration_ms == 0 || sprite_set.count < 2)
		return (texture_new_static(sprite_set.images[0]));
	texture.sprite_set = sprite_set;
	texture.image_index = 0;
	texture.image = sprite_set.images[0];
	if (duration_ms < 0)
	{
		texture.images_left = -1;
		texture.frames_left = -1;
	}
	else
	{
		texture.images_left = (int)sprite_set.count - 1;
		texture.frames_left = (int)fps_ms_to_frames((size_t)duration_ms);
	}
	return (texture);
}

void		texture_next(t_texture *texture)
{
	// No more frame
	if (texture->frames_left == 0)
		return ;
	// No more image
	if (texture->images_left == 0)
	{
		texture->frames_left = 0;
		return ;
	}
	// Inifinte loop
	if (texture->frames_left < 0)
	{
		texture->image_index = (texture->image_index + 1) % texture->sprite_set.count;
		texture->image = texture->sprite_set.images[texture->image_index];
		return ;
	}
	// Last frame
	if (texture->frames_left == 1)
	{
		texture->image_index = (texture->image_index + (size_t)texture->images_left) % texture->sprite_set.count;
		texture->image = texture->sprite_set.images[texture->image_index];
		texture->frames_left = 0;
		texture->images_left = 0;
		return ;
	}
	// frames > images
	if (texture->frames_left > texture->images_left)
	{
		if (texture->frames_left % texture->images_left == 0)
		{
			texture->image_index++;
			texture->image = texture->sprite_set.images[texture->image_index];
			texture->images_left--;
		}
		texture->frames_left--;
		return ;
	}
	// frames <= images
	texture->image_index += (size_t)(texture->images_left / texture->frames_left);
	texture->image = texture->sprite_set.images[texture->image_index];
	texture->frames_left--;
}
