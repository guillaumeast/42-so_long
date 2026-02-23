#include "hud_priv.h"
#include <stdlib.h>

# include "logs.h"

static bool hud_handler(int event_data, void *param);

bool	hud_load(t_controller *controller, t_data *data)
{
	controller->objects = malloc(HUD_OBJ_COUNT * sizeof * controller->objects);
	if (!controller->objects)
		return (false);
	controller->handler = hud_handler;
	if (!hud_background_create(data))
		return (false);
	if (!hud_loading_create(data))
		return (false);
	if (!hud_xav_create(data))
		return (false);
	return (true);
}

static bool hud_handler(int event_data, void *param)
{
	t_data			*data;
	t_controller	*controller;
	t_object		*loading;

	(void)event_data;
	print_warn("hud_handler()\n");

	data = (t_data *)param;
	controller = &data->control.controllers[CONTROLLER_HUD];
	loading = &controller->objects[HUD_OBJ_LOADING];
	loading->texture = texture_new_dynamic(SPRITE_SET_HUD_LOADING, 100);
	return (view_add(&data->view, loading));
}
