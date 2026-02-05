#include <CoreGraphics/CoreGraphics.h>
#include <stdio.h>

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	(void)mlx_ptr;
	CGDirectDisplayID	display;
	CGDisplayModeRef	mode;

	display = CGMainDisplayID();
	mode = CGDisplayCopyDisplayMode(display);
	if (!mode)
	{
		*sizex = 0;
		*sizey = 0;
		return (0);
	}
	*sizex = (int)CGDisplayModeGetPixelWidth(mode);
	*sizey = (int)CGDisplayModeGetPixelHeight(mode);
	CGDisplayModeRelease(mode);
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
