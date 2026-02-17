#include "mlx.h"
#include "window_priv.h"

# include <stdio.h>

static bool	window_compute_hud_pos(t_window *window);

void	window_init(t_window *window)
{
	window->mlx_win = NULL;
	window->height_px = 0;
	window->width_px = 0;
	window->cropped = false;
	window->moved = false;
	window->hud_y_pos_px = 0;
	window->hud_left_x_pos_px = 0;
	window->hud_mid_x_pos_px = 0;
	window->hud_right_x_pos_px = 0;
	window->map_y_pos_px = 0;
	window->map_x_pos_px = 0;
	window->map_y_cell_start = 0;
	window->map_y_cell_end = 0;
	window->map_x_cell_start = 0;
	window->map_x_cell_end = 0;
}

bool	window_load(void *mlx_ptr, t_window *window, t_map *map)
{
	int	display_height;
	int	display_width;

	mlx_get_screen_size(mlx_ptr, &display_width, &display_height);
	if (display_height < 0 || display_width < 0)
	{
		print_err(false, "mlx_get_screen_size() returned negative values");
		return (false);
	}
	window->height_px = display_height - WINDOW_OUT_PAD_Y_PX;
	window->width_px = display_width - WINDOW_OUT_PAD_X_PX;
	if (!window_compute_hud_pos(window) || !window_compute_map_pos(window, map))
		return (false);
	window_normalize_map(map);
	fprintf(stderr, "window = h%i x w%i\n", window->height_px, window->width_px);
	window->mlx_win = mlx_new_window(
		mlx_ptr,
		window->width_px,
		window->height_px,
		(char *)WINDOW_TITLE
	);
	if (!window->mlx_win)
		return (print_err(true, "mlx_new_window() failed"), false);
	return (true);
}

static bool	window_compute_hud_pos(t_window *window)
{
	int	extra_space;

	extra_space = window->width_px - WINDOW_HUD_WIDTH_PX;
	if (extra_space < 0)
	{
		print_err(false, "display is too small to render HUD");
		return (false);
	}
	window->hud_y_pos_px = WINDOW_IN_PAD_PX;
	window->hud_left_x_pos_px = WINDOW_IN_PAD_PX + extra_space / 2;
	window->hud_mid_x_pos_px = window->hud_left_x_pos_px
								+ SPRITES_HUD_LEFT_WIDTH_PX + WINDOW_IN_PAD_PX;
	window->hud_right_x_pos_px = window->hud_mid_x_pos_px
								+ SPRITES_HUD_MID_WIDTH_PX + WINDOW_IN_PAD_PX;
	return (true);
}

void	window_free(void *mlx_ptr, t_window *window)
{
	if (!mlx_ptr && window->mlx_win)
		mlx_destroy_window(mlx_ptr, window->mlx_win);
	window_init(window);
}
