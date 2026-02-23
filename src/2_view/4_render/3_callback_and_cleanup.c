#include "clock.h"
#include "render_priv.h"
#include <stdio.h>
#include <stdlib.h>

# include "logs.h"

static inline bool	should_rm_element(t_element_2D element_2D, uint ms_curr);

void	render_callback(t_render_queue *render_queue, uint ms_curr)
{
	t_callback_context	*context;
	uint				queue_len;
	uint				i;
	t_element_3D		*element_3D;

	context = &render_queue->context;
	queue_len = (uint)render_queue->count;
	i = 0;
	while (i < queue_len)
	{
		element_3D = render_queue->elements_3D[i];
		if (element_3D->on_frame)
			element_3D->on_frame(context, element_3D->data);
		if (element_3D->on_last && should_rm_element(element_3D->element_2D, ms_curr))
			element_3D->on_last(context, element_3D->data);
		i++;
	}
	clock_update_ms();
	print_pass("🔗 %4u callbacks executed (%2u ms)\n", i, clock_get()->ms_from_start - render_queue->context.ms_curr_frame);
}

void	render_cleanup(t_render_queue *render_queue, uint ms_curr)
{
	int				i;
	size_t			start_len;
	size_t			queue_len;
	t_element_3D	**queue;

	i = 0;
	queue = render_queue->elements_3D;
	queue_len = render_queue->count;
	start_len = queue_len;
	while ((size_t)i < queue_len)
	{
		if (should_rm_element(queue[i]->element_2D, ms_curr))
			render_rm(render_queue->elements_3D, &render_queue->count, i);
		i++;
	}
	clock_update_ms();
	print_pass("🔗 %4zu cleanup executed (%2u ms)\n", start_len - queue_len, clock_get()->ms_from_start - render_queue->context.ms_curr_frame);
}

static inline bool	should_rm_element(t_element_2D element_2D, uint ms_curr)
{
	return (element_2D.animation.ms_end < ms_curr
		&& element_2D.translation.ms_end < ms_curr);
}

void	render_rm(t_element_3D **queue, size_t *queue_len, int id)
{
	if (id < 0 || id >= (int)*queue_len)
		return ;
	queue[id]->render_pos = -1;
	if ((size_t)id + 1 < *queue_len)
	{
		queue[id] = queue[*queue_len - 1];
		queue[id]->render_pos = id;
	}
	(*queue_len)--;
	print_info("Render[%u] removed\n", (uint)id);
}
