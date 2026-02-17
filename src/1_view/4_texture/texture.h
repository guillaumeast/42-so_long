#ifndef TEXTURE_H
# define TEXTURE_H

# include "sprite_set.h"

typedef struct s_texture
{
	t_image			image;
	t_sprite_set	sprite_set;
	size_t			image_index;
	int				frames_left;
	int				images_left;
}	t_texture;

t_texture	texture_new_static(t_image image);
t_texture	texture_new_dynamic(t_sprite_set sprite_set, int duration_ms);
void		texture_next(t_texture *texture);

#endif
