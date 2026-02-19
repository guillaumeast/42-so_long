#include "mlx.h"
#include "apple.h"
#include "controller_priv.h"
#include "data.h"

# include "logs.h"

static int	handle_key_press(int event_data, void *param);
static int	handle_window_close(void *param);

bool	handlers_set(void *param)
{
	t_data	*data;

	print_title("handlers_set()");
	data = (t_data *)param;
	print_info("mlx_win = %p\n", data->view.mlx_win);
	mlx_hook(data->view.mlx_win, KEY_PRESS, KEY_PRESS_MASK, handle_key_press, param);
	print_pass("key_press hook set\n");
	mlx_hook(data->view.mlx_win, WINDOW_CLOSE, 0, handle_window_close, param);
	print_pass("window_close hook set\n");
	mlx_loop_hook(data->mlx_ptr, view_render, param);
	print_pass("view_render hook set\n");
	print_result("handlers_set");
	return (true);
}

static int	handle_key_press(int event_data, void *param)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)param;
	i = 0;
	while (i < CONTROLLER_COUNT)
	{
		if (data->control.controllers[i].handler)
			if (!data->control.controllers[i].handler(event_data, param))
				return (1);
		i++;
	}
	return (0);
}

static int	handle_window_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}
