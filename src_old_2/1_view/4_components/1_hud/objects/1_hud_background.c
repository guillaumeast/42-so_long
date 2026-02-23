#include "hud_priv.h"

# define HUD_BACKGROUND_OFFSET_Y	0
# define HUD_BACKGROUND_OFFSET_X	0

bool	hud_background_create(t_data *data)
{
	t_controller	*controller;
	t_object		*background;

	controller = &data->control.controllers[CONTROLLER_HUD];
	background = &controller->objects[HUD_OBJ_BACKGROUND];
	*background = object_new_static(
			HUD_BACKGROUND_OFFSET_Y,
			HUD_BACKGROUND_OFFSET_X,
			SPRITE_SET_HUD_BACKGROUND,
			SPRITE_HUD_BACKGROUND);
	return (view_add(&data->view, background));
}
