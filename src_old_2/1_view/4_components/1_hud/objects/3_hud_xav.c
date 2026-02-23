#include "hud_priv.h"

# include <stdio.h>

#define XAV_INTRO_MS		10000
#define XAV_OFFSET_Y		705
#define XAV_OFFSET_X		1290

#define XAV_PLAY_RATIO_1	2
#define XAV_PLAY_RATIO_2	1

static bool	hud_xav_play_end(void *param, struct s_object *object);

bool	hud_xav_create(t_data *data)
{
	t_controller	*controller;
	t_object		*xav;

	controller = &data->control.controllers[CONTROLLER_HUD];
	xav = &controller->objects[HUD_OBJ_XAV];
	*xav = object_new_static(
		XAV_OFFSET_Y,
		XAV_OFFSET_X,
		SPRITE_SET_XAV,
		SPRITE_XAV_NO);
	return (hud_xav_play(data));
}

bool	hud_xav_play(t_data *data)
{
	t_object	*xav;

	xav = &data->control.controllers[CONTROLLER_HUD].objects[HUD_OBJ_XAV];
	xav->texture = texture_new_dynamic(SPRITE_SET_XAV, XAV_INTRO_MS);
	object_add_callback(data, xav, hud_xav_play_end, CALLBACK_EACH_FRAME);
	hud_loading_play(data, HUD_LOADING_MS * 4);
	return (view_add(&data->view, xav));
}

static bool	hud_xav_play_end(void *param, struct s_object *object)
{
	t_object	*loading;

	loading = &((t_data *)param)->control.controllers[CONTROLLER_HUD].objects[HUD_OBJ_LOADING];
	if (loading->status != OBJ_STATUS_QUEUED && object->status == OBJ_STATUS_QUEUED)
		return (hud_loading_play(param, HUD_LOADING_MS * 2));
	else if (object->status != OBJ_STATUS_QUEUED)
	{
		object->callback_mode = CALLBACK_NONE;
		object->fn_callback = NULL;
		return (hud_loading_play(param, HUD_LOADING_MS));
	}
	return (true);
}
