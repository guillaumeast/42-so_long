#include "object.h"
#include "mlx.h"

# include <stdio.h>

t_object	object_new(t_object_type type, t_position position, t_size size, t_texture texture)
{
	static size_t	id = 0;

	return ((t_object)
		{
			.id = id++,
			.type = type,
			.position = position,
			.size = size,
			.texture = texture
		});
}

void	object_render(void *mlx_ptr, void *win_ptr, t_object *object)
{
	if (object->position.frames_left == 0
		&& object->size.frames_left == 0
		&& object->texture.frames_left == 0)
		return ;
	mlx_put_image_to_window(
		mlx_ptr,
		win_ptr,
		object->texture.image,
		object->position.x,
		object->position.y);
	position_next(&object->position);
	size_next(&object->size);
	texture_next(&object->texture);
	fprintf(stderr, "RENDERED => id = %zu (%3i | %3i | %3i)\n", object->id, object->position.frames_left, object->size.frames_left, object->texture.frames_left);
}
