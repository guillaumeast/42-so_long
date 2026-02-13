#include "window_priv.h"

static inline bool	window_compute_map_pos_y(t_window *window, t_map *map);
static inline bool	window_compute_map_pos_x(t_window *window, t_map *map);
static inline void	window_center_map_y(t_window *window, t_map *map);
static inline void	window_center_map_x(t_window *window, t_map *map);

bool	window_compute_map_pos(t_window *window, t_map *map)
{
	window->map_y_cell_start = 0;
	window->map_y_cell_end = map->height - 1;
	window->map_x_cell_start = 0;
	window->map_x_cell_end = map->width - 1;
	if (!window_compute_map_pos_y(window, map))
		return (false);
	if (!window_compute_map_pos_x(window, map))
		return (false);
	return (true);
}

static inline bool	window_compute_map_pos_y(t_window *window, t_map *map)
{
	int	available_height;
	int	extra_height;

	available_height = window->height_px - WINDOW_HUD_HEIGHT_PX;
	if (available_height < (2 * WINDOW_PLAYER_PAD_SP + 1) * SPRITES_MAP_HEIGHT_PX)
	{
		print_err(false, "display is too small to render both HUD and map");
		return (false);
	}
	while (window->map_y_cell_end * SPRITES_MAP_HEIGHT_PX > available_height)
		window->map_y_cell_end--;
	extra_height = available_height - (window->map_y_cell_end + 1) * SPRITES_MAP_HEIGHT_PX;
	if (extra_height >= 0)
		window->map_y_pos_px = WINDOW_HUD_HEIGHT_PX + extra_height / 2;
	else
		window->map_y_pos_px = WINDOW_HUD_HEIGHT_PX;
	if (window->map_y_cell_end < map->height - 1)
	{
		window->cropped = true;
		window_center_map_y(window, map);
	}
	return (true);
}

static inline bool	window_compute_map_pos_x(t_window *window, t_map *map)
{
	int	extra_width;

	while (window->map_x_cell_end * SPRITES_MAP_HEIGHT_PX > window->width_px)
		window->map_x_cell_end--;
	if (window->map_x_cell_end < 2 * WINDOW_PLAYER_PAD_SP + 1)
	{
		print_err(false, "display width is too small to render the map");
		return (false);
	}
	extra_width = window->width_px - (window->map_x_cell_end + 1) * SPRITES_MAP_WIDTH_PX;
	if (extra_width >= 0)
		window->map_x_pos_px = extra_width / 2;
	else
		window->map_x_pos_px = 0;
	if (window->map_x_cell_end < map->width - 1)
	{
		window->cropped = true;
		window_center_map_x(window, map);
	}
	return (true);
}

static inline void	window_center_map_y(t_window *window, t_map *map)
{
	while (window->map_y_cell_end < map->player.y + WINDOW_PLAYER_PAD_SP
		&& window->map_y_cell_end < map->height - 1)
	{
		window->map_y_cell_start++;
		window->map_y_cell_end++;
	}
}

static inline void	window_center_map_x(t_window *window, t_map *map)
{
	while (window->map_x_cell_end < map->player.x + WINDOW_PLAYER_PAD_SP
		&& window->map_x_cell_end < map->width - 1)
	{
		window->map_x_cell_start++;
		window->map_x_cell_end++;
	}
}
