#ifndef TEXTURE_H
# define TEXTURE_H

# include "sprite_set.h"

// typedef struct s_texture
// {
// 	t_image			image;
// 	t_sprite_set	sprite_set;
// 	size_t			image_index;
// 	int				frames_left;
// 	int				images_left;
// }	t_texture;

typedef struct s_texture
{
	t_image			image;
	t_sprite_set	sprite_set;
	int				image_index;
	int				frames_rendered;
	int				frames_total;
	int				frames_left;
	bool			must_be_rendered;
}	t_texture;

t_texture	texture_new_static(t_sprite_set_id set_id, size_t image_id);
t_texture	texture_new_dynamic(t_sprite_set_id set_id, size_t duration_ms);
void		texture_next(t_texture *texture);
void		texture_print(t_texture *texture);

#endif
