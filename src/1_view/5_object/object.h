#ifndef OBJECT_H
# define OBJECT_H

# include "position.h"
# include "size.h"
# include "texture.h"

typedef enum e_object_type
{
	OBJECT_HUD_BACKGROUND,
	OBJECT_HUD_LOADING,
	// OBJECT_HUD_EYE,
	// OBJECT_HUD_SCREEN,
	// OBJECT_MAP,
	// OBJECT_PLAYER,
	OBJECT_COUNT
}	t_object_type;

typedef struct s_object
{
	size_t			id;
	t_object_type	type;
	t_position		position;
	t_size			size;
	t_texture		texture;
}	t_object;

t_object	object_new(t_object_type type, t_position position, t_size size, t_texture texture);
void		object_render(void *mlx_ptr, void *win_ptr, t_object *object);

// t_object	*object_new(t_object *parent, t_pixel position, t_size size, t_skin skin);
// void		object_set_image(t_object *object, t_image image);
// void		object_set_animation(t_object *object, t_animation_id animation_id, size_t duration_ms);
// void		object_set_movement(t_object *object, t_pixel target_position, size_t duration_ms);
// void		object_free(t_object **object);	// Delete object and its children

#endif
