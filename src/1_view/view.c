#include "view.h"
#include "libft.h"
#include "apple.h"
#include "mlx.h"
#include <stdlib.h>

# include "logs.h"

#define VIEW_INITIAL_QUEUE_CAP 128

t_view	view_init(void)
{
	return ((t_view)
		{
			.mlx_win = NULL,
			.height = 0,
			.width = 0,
			.time.ms = 0,
			.time.frames = 0,
			.time.fps = 0,
			.sprite_sets = sprite_set_init(),
			.queue = NULL,
			.queue_len = 0,
			.queue_cap = 0
		});
}

bool	view_load(void *mlx_ptr, t_view *view)
{
	char	*title;

	print_title("view_load()");
	if (!sprite_set_load(mlx_ptr))
		return (false);
	view->queue = malloc(VIEW_INITIAL_QUEUE_CAP * sizeof * view->queue);
	if (!view->queue)
		return (false);
	print_pass("queue malloc'd\n");
	view->queue_cap = VIEW_INITIAL_QUEUE_CAP;
	mlx_get_screen_size(mlx_ptr, &view->width, &view->height);
	if (view->height < 0 || view->width < 0)
	{
		print_err(true, "mlx_get_screen_size() failed");
		return (false);
	}
	// if (view->height < WINDOW_MIN_HEIGHT || view->width < WINDOW_MIN_WIDTH)
	// {
	// 	fprint_err(false,
	// 		"screen is too small",
	// 		" => height: %i (min: %i) | width: %i (min: %i))",
	// 		view->height, WINDOW_MIN_HEIGHT, view->width, WINDOW_MIN_WIDTH);
	// 	return (false);
	// }
	print_pass("screen size captures\n");
	title = str_dup(WINDOW_TITLE);
	if (!title)
		return (false);
	view->width = WINDOW_MIN_WIDTH;
	view->height = WINDOW_MIN_HEIGHT;
	view->mlx_win = mlx_new_window(
		mlx_ptr,
		WINDOW_MIN_WIDTH,
		WINDOW_MIN_HEIGHT,
		title
	);
	free(title);
	if (!view->mlx_win)
		return (print_err(true, "mlx_new_window() failed"), false);
	print_result("view loaded");
	return (true);
}

void	view_free(void *mlx_ptr, t_view *view)
{
	if (mlx_ptr)
		sprite_set_free(mlx_ptr);
	if (view->queue)
		free(view->queue);
	*view = view_init();
}
