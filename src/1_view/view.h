#ifndef VIEW_H
# define VIEW_H

# include "sprite_set.h"
# include "object.h"

# define WINDOW_TITLE		"so_long"
# define WINDOW_MIN_HEIGHT	SPRITE_SET_HUD_BACKGROUND_HEIGHT_PX
# define WINDOW_MIN_WIDTH	SPRITE_SET_HUD_BACKGROUND_WIDTH_PX

typedef struct s_view
{
	void			*mlx_win;
	t_sprite_set	sprite_sets[SPRITE_SET_COUNT];		// All available sprite_sets
	t_object		objects[OBJECT_COUNT];				// Instanced objects
}	t_view;

typedef struct s_tmp
{
	void	*mlx_ptr;
	t_view	view;
}	t_tmp;

void	view_init(t_view *view);
bool	view_load(void *mlx_ptr, t_view *view);
bool	view_launch(void *mlx_ptr, t_view *view);
void	view_free(void *mlx_ptr, t_view *view);

#endif
