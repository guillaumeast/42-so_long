#ifndef VIEW_MLX_H
# define VIEW_MLX_H

# include <stdbool.h>

/* ************************************************************************* */
/*                                  MY MLX                                   */
/* ************************************************************************* */
/*
** [SEE] view_settings.h	=> settings
** [>>>] view_mlx.h			=> (here you are)
** [SEE] view_skin.h		=> image loading module
** [SEE] view_element.h		=> render element constructor
** [SEE] view_render.h		=> rendering module
** [SEE] view.h				=> external user api
**
** Abstraction of sh*!#y mlx and implementation of missing macOS version functions.
*/

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef void	*t_img;

// 24 bytes
typedef struct s_mlx
{
	void	*mlx_ptr;	// Owned
	void	*mlx_win;	// Owned
	int		win_height;
	int		win_width;
}	t_mlx;

/* ************************************************************************* */
/*                              FRAMEWORK API                                */
/* ************************************************************************* */

t_mlx	*view_mlx_get(void);
bool	view_mlx_load(int height, int width, const char *title);
void	view_mlx_free(void);

t_img	view_mlx_img_new(char *folder_name, int height, int width);
t_img	view_mlx_img_free(t_img img);

# ifdef __APPLE__
int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int mlx_loop_end (void *mlx_ptr);
int	mlx_destroy_display(void *mlx_ptr);
# endif

#endif
