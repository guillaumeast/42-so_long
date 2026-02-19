#ifndef SPRITE_SET_PRIV_H
# define SPRITE_SET_PRIV_H

# include "sprite_set.h"

t_sprite_set	*sprite_set_addr(void);
bool			sprite_set_init_dispatch(t_sprite_set *sprite_set);
bool			load_image(
					void *mlx_ptr,
					char *path,
					t_sprite_set *sprite_set,
					size_t sprite_index);

#endif
