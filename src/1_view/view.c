#include "view.h"
#include "libft.h"
#include "apple.h"
#include "mlx.h"

# include <stdio.h>
# include "logs.h"
# include "fps.h"
void	load_objects(t_view *view);
int	render(t_tmp *tmp);

void	view_init(t_view *view)
{
	view->mlx_win = NULL;
	sprite_set_init_all(&view->sprite_sets);
}

bool	view_load(void *mlx_ptr, t_view *view)
{
	if (!sprite_set_load_all(mlx_ptr, &view->sprite_sets))
		return (false);
	load_objects(view);	// TMP
	return (true);
}

bool	view_launch(void *mlx_ptr, t_view *view)
{
	int	display_height;
	int	display_width;
	t_tmp	tmp;

	mlx_get_screen_size(mlx_ptr, &display_width, &display_height);
	if (display_height < 0 || display_width < 0)
	{
		print_err(false, "mlx_get_screen_size() returned negative values");
		return (false);
	}
	// if (display_height < WINDOW_MIN_HEIGHT || display_width < WINDOW_MIN_WIDTH)
	// {
	// 	fprint_err(false,
	// 		"screen is too small",
	// 		" => height: %i (min: %i) | width: %i (min: %i))",
	// 		display_height, WINDOW_MIN_HEIGHT, display_width, WINDOW_MIN_WIDTH);
	// 	return (false);
	// }
	tmp.mlx_ptr = mlx_ptr;
	tmp.view = *view;
	tmp.view.mlx_win = mlx_new_window(
		mlx_ptr,
		WINDOW_MIN_WIDTH,
		WINDOW_MIN_HEIGHT,
		(char *)WINDOW_TITLE
	);
	if (!tmp.view.mlx_win)
		return (print_err(true, "mlx_new_window() failed"), false);
	mlx_loop_hook(mlx_ptr, render, &tmp);
	mlx_loop(mlx_ptr);
	return (true);
}

void	view_free(void *mlx_ptr, t_view *view)
{
	if (!mlx_ptr)
		return ;
	sprite_set_free_all(mlx_ptr, &view->sprite_sets);
}

/* --- TMP --- */

void	load_objects(t_view *view)
{
	view->objects[OBJECT_HUD_BACKGROUND] = object_new(
		OBJECT_HUD_BACKGROUND,
		position_new_static(0, 0),
		size_new_static(
			SPRITE_SET_HUD_BACKGROUND_HEIGHT_PX,
			SPRITE_SET_HUD_BACKGROUND_WIDTH_PX),
		texture_new_static(
			view->sprite_sets[SPRITE_SET_HUD_BACKGROUND]
			.images[SPRITE_HUD_BACKGROUND]));
	view->objects[OBJECT_HUD_LOADING] = object_new(
		OBJECT_HUD_LOADING,
		position_new_static(819, 0),
		size_new_dynamic(
			SPRITE_SET_HUD_LOADING_HEIGHT_PX,
			SPRITE_SET_HUD_LOADING_WIDTH_PX, -1, 3000),
		texture_new_static(view->sprite_sets[SPRITE_SET_HUD_LOADING].images[SPRITE_HUD_LOADING_1]));
	// view->objects[OBJECT_HUD_LOADING] = object_new(
	// 	OBJECT_HUD_LOADING,
	// 	position_new_static(819, 0),
	// 	size_new_static(
	// 		SPRITE_SET_HUD_LOADING_HEIGHT_PX,
	// 		SPRITE_SET_HUD_LOADING_WIDTH_PX),
	// 	texture_new_dynamic(view->sprite_sets[SPRITE_SET_HUD_LOADING], 500));
}

int	render(t_tmp *tmp)
{
	size_t	i;

	if (!fps_should_render())
		return (0);
	i = 0;
	while (i < OBJECT_COUNT)
	{
		object_render(tmp->mlx_ptr, tmp->view.mlx_win, &tmp->view.objects[i]);
		i++;
	}
	return (0);
}
