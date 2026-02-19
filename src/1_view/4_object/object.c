#include "object.h"
#include "data.h"

# include "logs.h"

t_callback	callback_new(
	bool			(*fn_callback)(void *param, struct s_object *object),
	t_callback_mode	mode)
{
	if (!fn_callback || mode == CALLBACK_NONE)
		return ((t_callback) { 0 });
	return ((t_callback)
		{
			.fn_callback = fn_callback,
			.mode = mode
		});
}

bool	object_add_callback(
	void 			*param,
	t_object		*object,
	bool			(*fn_callback)(void *param, struct s_object *object),
	t_callback_mode	mode)
{
	t_data	*data;

	if (!fn_callback || mode == CALLBACK_NONE)
	{
		object->fn_callback = NULL;
		object->callback_mode = CALLBACK_NONE;
		return (true);
	}
	object->fn_callback = fn_callback;
	object->callback_mode = mode;
	data = (t_data *)param;
	return (view_add(&data->view, object));
}

t_object	object_new(
	t_position 		position,
	t_texture 		texture,
	bool			(*fn_callback)(void *param, struct s_object *object),
	t_callback_mode	mode)
{
	static size_t	count = 0;
	t_object		object;

	print_pass("object created [%zu]\n", count++);
	object.status = OBJ_STATUS_HIDDEN;
	object.position = position;
	object.texture = texture;
	object.background_count = 0;
	if (!fn_callback || mode == CALLBACK_NONE)
	{
		object.fn_callback = NULL;
		object.callback_mode = CALLBACK_NONE;
	}
	else
	{
		object.fn_callback = fn_callback;
		object.callback_mode = mode;
	}
	return (object);
}

t_object	object_new_static(int y, int x, t_sprite_set_id set_id, size_t image_id)
{
	return (object_new(
		position_new_static(y, x),
		texture_new_static(set_id, image_id),
		NULL,
		CALLBACK_NONE
	));
}

void	object_print(t_object *object)
{
	fprintf(stderr, "╭── 📦 object %p\n", object);
	fprintf(stderr, "│ status = %i", object->status);
	if (object->status == OBJ_STATUS_HIDDEN)
		fprintf(stderr, " (hidden)\n");
	else if (object->status == OBJ_STATUS_QUEUED)
		fprintf(stderr, " (queued)\n");
	else if (object->status == OBJ_STATUS_RENDERING)
		fprintf(stderr, " (rendering)\n");
	else if (object->status == OBJ_STATUS_RENDERED)
		fprintf(stderr, " (rendered)\n");
	else
		fprintf(stderr, " (unknown)\n");
	fprintf(stderr, "│ ");
	position_print(&object->position);
	fprintf(stderr, "│ ");
	texture_print(&object->texture);
	if (object->callback_mode != CALLBACK_NONE)
	{
		if (object->callback_mode == CALLBACK_EACH_FRAME)
			fprintf(stderr, "│ callback on each frame => %p\n", object->fn_callback);
		else if (object->callback_mode == CALLBACK_LAST_FRAME)
			fprintf(stderr, "│ callback on last frame => %p\n", object->fn_callback);
	}
	fprintf(stderr, "╰──\n");
}
