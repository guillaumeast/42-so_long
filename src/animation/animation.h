#ifndef ANIMATION_H
# define ANIMATION_H

# include "sprites.h"
# include "map.h"

typedef struct s_animation
{
	t_image	*sprites;
	size_t	sprites_count;
	size_t	current_sprite;
}	t_animation;

typedef struct s_object
{
	t_cell		current_cell;
	t_cell		target_cell;
	bool		is_moving;
	t_animation	animation;
}	t_object;

#endif
