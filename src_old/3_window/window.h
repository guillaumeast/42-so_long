#ifndef WINDOW_H
# define WINDOW_H

# include "libft.h"
# include "map.h"
# include <stdbool.h>

# ifdef __APPLE__
int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int mlx_loop_end (void *mlx_ptr);
int	mlx_destroy_display(void *mlx_ptr);
# endif

# define WINDOW_TITLE				"so_long"

# define WINDOW_IN_PAD_PX			16

# ifdef __APPLE__
# define WINDOW_OUT_PAD_Y_PX		65
# define WINDOW_OUT_PAD_X_PX		0
# else
# define WINDOW_OUT_PAD_Y_PX		100
# define WINDOW_OUT_PAD_X_PX		100
# endif

# define WINDOW_HUD_HEIGHT_PX		(2 * WINDOW_IN_PAD_PX + SPRITES_HUD_LEFT_HEIGHT_PX)
# define WINDOW_HUD_WIDTH_PX		(4 * WINDOW_IN_PAD_PX + SPRITES_HUD_LEFT_WIDTH_PX + SPRITES_HUD_MID_WIDTH_PX + SPRITES_HUD_RIGHT_WIDTH_PX)

# define WINDOW_HUD_Y_POS_PX		WINDOW_IN_PAD_PX
# define WINDOW_HUD_LEFT_X_POS_PX	WINDOW_IN_PAD_PX
# define WINDOW_HUD_MID_X_POS_PX	(WINDOW_HUD_LEFT_X_POS_PX + SPRITES_HUD_LEFT_WIDTH_PX + WINDOW_IN_PAD_PX)
# define WINDOW_HUD_RIGHT_X_POS_PX	(WINDOW_HUD_MID_X_POS_PX + SPRITES_HUD_MID_WIDTH_PX + WINDOW_IN_PAD_PX)

# define WINDOW_MIN_HEIGHT			(WINDOW_HUD_HEIGHT_PX + MAP_BONUS_HEIGHT)
# define WINDOW_MIN_WIDTH			max(WINDOW_HUD_WIDTH_PX, MAP_BONUS_WIDTH)
# define WINDOW_PLAYER_PAD_SP		2

typedef struct s_window
{
	void	*mlx_win;
	int		height_px;
	int		width_px;
	bool	cropped;
	bool	moved;
	int		hud_y_pos_px;
	int		hud_left_x_pos_px;
	int		hud_mid_x_pos_px;
	int		hud_right_x_pos_px;
	int		map_y_pos_px;
	int		map_x_pos_px;
	int		map_y_cell_start;
	int		map_x_cell_start;
	int		map_y_cell_end;
	int		map_x_cell_end;
}	t_window;

void	window_init(t_window *window);
bool	window_load(void *mlx_ptr, t_window *window, t_map *map);
void	window_free(void *mlx_ptr, t_window *window);

#endif
