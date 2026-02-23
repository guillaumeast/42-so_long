#include "mlx.h"
#include "view_mlx.h"
#include "controller_priv.h"
#include "view.h"
#include <stdlib.h>

# include "logs.h"

static int	handle_tick(t_controller *controller);
static int	handle_event(int event, t_controller *controller);
static int	handle_window_close(t_controller *controller);

void	controller_set_handlers(void)
{
	t_mlx			mlx;
	t_controller	*controller;

	mlx = *view_mlx_get();
	controller = controller_get();
	mlx_hook(mlx.mlx_win, KEY_PRESS, KEY_PRESS_MASK, handle_event, controller);
	mlx_hook(mlx.mlx_win, WINDOW_CLOSE, 0, handle_window_close, mlx.mlx_ptr);
	mlx_loop_hook(mlx.mlx_ptr, handle_tick, controller);
	print_pass("hooks loaded\n");
}

static int	handle_tick(t_controller *controller)
{
	static uint			next_frame_ms = 0;
	size_t				tick_ms;

	clock_update(true, false);
	tick_ms = clock_get()->ms_from_start;
	if (tick_ms < next_frame_ms)
		return (0);
	view_flush();
	propagate_frame(controller, *clock_get());
	next_frame_ms += tick_ms + (1000 / FPS);
	print_warn("[ ⚡️ | tick_ms = %zu | next_frame_ms = %u ]\n", tick_ms, next_frame_ms);
	return (0);
}

static int	handle_event(int event, t_controller *controller)
{
	if (event == KEY_ESC)
		controller_stop();
	else
		propagate_event(controller, event);
	print_pass("[ ⌨️ | event %i handled ]\n", event);
	return (0);
}

static int	handle_window_close(t_controller *controller)
{
	(void)controller;
	print_warn("[ ❌ | Window closed ]\n");
	mlx_loop_end(view_mlx_get()->mlx_ptr);
	return (0);
}
