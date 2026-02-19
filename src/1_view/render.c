#include "data.h"
#include "fps.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

# include "logs.h"
# include <stdio.h>

static inline void	render_object(void *mlx_ptr, void *win_ptr, t_object *object, size_t *count);

bool	view_add(t_view *view, t_object *object)
{
	t_object	**new_queue;
	
	if (object->status == OBJ_STATUS_QUEUED)
		return (true);
	if (view->queue_len == view->queue_cap)
	{
		fprintf(stderr, "Growing from %4zu...\n", view->queue_cap);
		new_queue = malloc(2 * view->queue_cap * sizeof * new_queue);
		if (!new_queue)
			return (false);
		ft_memcpy(new_queue, view->queue, view->queue_len);
		free(view->queue);
		view->queue = new_queue;
		view->queue_cap *= 2;
		fprintf(stderr, "=> Grown to  %4zu\n", view->queue_cap);
	}
	view->queue[view->queue_len] = object;
	view->queue_len++;
	object->status = OBJ_STATUS_QUEUED;
	return (true);
}

int		view_render(void *param)
{
	t_data		*data;
	size_t		i;
	t_object	*object;
	size_t		start_ms;
	size_t		count;

	data = (t_data *)param;
	start_ms = fps_time_in_ms();
	if (start_ms - data->view.time.ms < 1000 / FPS)
		return (0);
	count = 0;
	i = 0;
	while (i < data->view.queue_len)
	{
		object = data->view.queue[i];
		render_object(data->mlx_ptr, data->view.mlx_win, object, &count);
		if (object->position.frames_left == 0 && object->texture.frames_left == 0)
		{
			object->status = OBJ_STATUS_RENDERED;
			if (i != data->view.queue_len - 1)
				data->view.queue[i] = data->view.queue[data->view.queue_len - 1];
			data->view.queue_len--;
			if (object->callback_mode != CALLBACK_NONE && object->fn_callback)
				if (!object->fn_callback(param, object))
					return (false);
			continue ;
		}
		object->status = OBJ_STATUS_QUEUED;
		if (object->callback_mode == CALLBACK_EACH_FRAME && object->fn_callback)
			if (!object->fn_callback(param, object))
				return (false);
		i++;
	}
	fps_update_time(&data->view.time);
	if (count > 0)
		print_pass("🎬 frame [%9zu] at %9zu ms ====> %3zu objects rendered in %3zu ms (%2zu fps)\n", data->view.time.frames, data->view.time.ms, count, data->view.time.ms - start_ms, data->view.time.fps);
	return (0);
}

static inline void	render_object(void *mlx_ptr, void *win_ptr, t_object *object, size_t *count)
{
	size_t		i;

	object->status = OBJ_STATUS_RENDERING;
	i = 0;
	while (i < object->background_count)
	{
		render_object(mlx_ptr, win_ptr, object->backgrounds[i], count);
		i++;
	}
	// object_print(object);
	mlx_put_image_to_window(
		mlx_ptr,
		win_ptr,
		object->texture.image,
		object->position.x,
		object->position.y);
	position_next(&object->position);
	texture_next(&object->texture);
	(*count)++;
}
