#include "view_mlx.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

# include "logs.h"

t_mlx	*view_mlx_get(void)
{
	static t_mlx mlx = { 0 };

	return (&mlx);
}

bool	view_mlx_load(int height, int width, const char *title)
{
	t_mlx	*mlx;
	char	*mallocd_title;

	mlx = view_mlx_get();
	mallocd_title = str_dup(title);
	if (!mallocd_title)
	{
		print_err(true, "str_dup() failed to dup window title");
		return (false);
	}
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (free(mallocd_title), print_err(true, "mlx_init() failed"), false);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, width, height, mallocd_title);
	if (!mlx->mlx_win)
		return (free(mallocd_title), print_err(true, "mlx_new_window() failed"), false);
	mlx->win_height = height;
	mlx->win_width = width;
	free(mallocd_title);
	print_pass("mlx initialized ");
	print_info("[ 🖥️ | h%i x w%i ]\n", height, width);
	return (true);
}

t_img	view_mlx_img_new(char *path, int height, int width)
{
	int		r_height;
	int		r_width;
	t_img	img;

	img = mlx_png_file_to_image(
		view_mlx_get()->mlx_ptr,
		path,
		&r_width,
		&r_height);
	if (!img)
	{
		fprint_err(true,
			"Unable to load sprite", " %s", path);
		return (NULL);
	}
	if (r_width != width || r_height != height)
	{
		fprint_err(false,
			"Invalid sprite size",
			" '%s': width = %i x height = %i (expected %i x %i)",
			path, r_width, r_height, width, height);
		return (NULL);
	}
	print_pass("image '%s' loaded\n", path);
	return (img);
}

t_img	view_mlx_img_free(t_img img)
{
	mlx_destroy_image(view_mlx_get()->mlx_ptr, img);
	return ((t_img){ 0 });
}

void	view_mlx_free(void)
{
	t_mlx	*mlx;

	mlx = view_mlx_get();
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	if (mlx->mlx_ptr)
		mlx_destroy_display(mlx->mlx_ptr);
}
