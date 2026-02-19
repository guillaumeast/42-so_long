#ifndef VIEW_H
# define VIEW_H

# include "fps.h"
# include "sprite_set.h"
# include "object.h"

# define WINDOW_TITLE			"so_long"
# define WINDOW_MIN_HEIGHT		SPRITE_SET_HUD_BACKGROUND_HEIGHT_PX
# define WINDOW_MIN_WIDTH		SPRITE_SET_HUD_BACKGROUND_WIDTH_PX

typedef struct s_view
{
	void			*mlx_win;		// Owned
	int				height;
	int				width;
	t_time			time;
	t_sprite_set	*sprite_sets;	// Borrowed
	t_object		**queue;		// Owned list of borrowed pointers
	size_t			queue_len;
	size_t			queue_cap;
}	t_view;

/* --- view.c --- */

t_view	view_init(void);
bool	view_load(void *mlx_ptr, t_view *view);
void	view_free(void *mlx_ptr, t_view *view);

/* --- render.c --- */

bool	view_add(t_view *view, t_object *object);
int		view_render(void *param);

#endif
