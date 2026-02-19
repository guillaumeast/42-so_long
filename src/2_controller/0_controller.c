#include "controller_priv.h"
#include <stdlib.h>

# include "logs.h"

static void	controller_free_rec(t_controller *controller);

t_control	control_init(void)
{
	t_control	control;
	size_t		i;

	i = 0;
	while (i < CONTROLLER_COUNT)
	{
		control.controllers[i] = (t_controller){ 0 };
		i++;
	}
	return (control);
}

bool	control_load(t_control *control, void *param)
{
	print_title("control_load()");
	if (!hud_load(&control->controllers[CONTROLLER_HUD], param))
		return (false);
	print_pass("hud loaded\n");
	if (!handlers_set(param))
		return (false);
	print_pass("handlers set\n");
	print_result("control loaded");
	return (true);
}

void		control_free(t_control *control)
{
	size_t		i;

	i = 0;
	while (i < CONTROLLER_COUNT)
	{
		controller_free_rec(&control->controllers[i]);
		i++;
	}
}

static void	controller_free_rec(t_controller *controller)
{
	size_t	i;

	if (controller->controllers)
	{
		i = 0;
		while (i < controller->controller_len)
		{
			controller_free_rec(&controller->controllers[i]);
			i++;
		}
		free(controller->controllers);
	}
	if (controller->objects)
		free(controller->objects);
	*controller = (t_controller){ 0 };
}
