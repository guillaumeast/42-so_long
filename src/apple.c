#include <CoreGraphics/CoreGraphics.h>

# include "logs.h"

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	CGDirectDisplayID	window_id;

	(void)mlx_ptr;
	window_id = CGMainDisplayID();
	*sizex = (int)CGDisplayPixelsWide(window_id);
	*sizey = (int)CGDisplayPixelsHigh(window_id);
	return (0);
}

int mlx_loop_end (void *mlx_ptr)
{
	(void)mlx_ptr;
	print_result("exit instead of unavailable mlx_loop_end");
	exit(EXIT_SUCCESS);
}

int	mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	print_info("mlx_destroy_display() unavailable on mlx-mac");
	return (0);
}
