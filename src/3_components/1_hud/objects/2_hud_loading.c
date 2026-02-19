#include "hud_priv.h"

# include <stdio.h>

# define HUD_LOADING_OFFSET_Y		817
# define HUD_LOADING_OFFSET_X		0

bool	hud_loading_create(t_data *data)
{
	t_controller	*controller;
	t_object		*loading;

	controller = &data->control.controllers[CONTROLLER_HUD];
	loading = &controller->objects[HUD_OBJ_LOADING];
	*loading = object_new_static(
		HUD_LOADING_OFFSET_Y,
		HUD_LOADING_OFFSET_X,
		SPRITE_SET_HUD_LOADING,
		SPRITE_HUD_LOADING_0);
	// controller->objects[HUD_OBJ_LOADING].backgrounds[0] = &controller->objects[HUD_OBJ_BACKGROUND];
	// controller->objects[HUD_OBJ_LOADING].background_count = 1;
	return (true);
}

bool	hud_loading_play(t_data *data, size_t duration_ms)
{
	t_object	*object;

	object = &data->control.controllers[CONTROLLER_HUD].objects[HUD_OBJ_LOADING];
	object->texture = texture_new_dynamic(SPRITE_SET_HUD_LOADING, duration_ms);
	object_add_callback(data, object, hud_loading_callback, CALLBACK_LAST_FRAME);
	// TMP
	object_print(object);
	//
	return (view_add(&data->view, object));
}

bool	hud_loading_callback(void *data, struct s_object *object)
{
	int		next_frame_count;
	size_t	next_ms_count;

	(void)data;
	next_frame_count = object->texture.frames_total / 2;
	if (next_frame_count <= (int)object->texture.sprite_set.count)
	{
		object->callback_mode = CALLBACK_NONE;
		object->fn_callback = NULL;
		return (true);
	}
	next_ms_count = fps_frames_to_ms((size_t)next_frame_count);
	object->texture = texture_new_dynamic(SPRITE_SET_HUD_LOADING, next_ms_count);
	return (true);
}
