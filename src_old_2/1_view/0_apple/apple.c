#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	CGDirectDisplayID	window_id;

	(void)mlx_ptr;
	window_id = CGMainDisplayID();
	*sizex = (int)CGDisplayPixelsWide(window_id);
	*sizey = (int)CGDisplayPixelsHigh(window_id);
	return (1);
}

int mlx_loop_end (void *mlx_ptr)
{
	(void)mlx_ptr;
	exit(EXIT_SUCCESS);
}

int	mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (1);
}
#endif
