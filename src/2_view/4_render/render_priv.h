#ifndef RENDER_PRIV_H
# define RENDER_PRIV_H

# include "view_mlx.h"
# include "view_element.h"

# define RENDER_QUEUE_CAP	128

// 1056 bytes
typedef struct s_render_queue
{
	t_callback_context	context;
	size_t				count;
	t_element_3D		*elements_3D[RENDER_QUEUE_CAP];
}	t_render_queue;

/* --- display_and_update.c --- */

void	render_display_backgrounds(t_element_3D **queue, size_t count, t_mlx mlx, uint ms_curr);
void	render_display_and_update_foregrounds(t_element_3D **queue, size_t count, t_mlx mlx, uint ms_curr);

/* --- callback_and_cleanup.c --- */

void	render_callback(t_render_queue *render_queue, uint ms_curr);
void	render_cleanup(t_render_queue *render_queue, uint ms_curr);
void	render_rm(t_element_3D **queue, size_t *queue_len, int id);

#endif
