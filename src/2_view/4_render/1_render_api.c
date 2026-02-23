#include "render_priv.h"
#include "clock.h"
#include <stdio.h>
#include <stdlib.h>

# include "logs.h"

static inline t_render_queue		*render_queue_get(void);
static inline t_callback_context	populate_context(t_callback_context prev_context, t_clock clock);

bool	render_element(t_element_3D *element)
{
	t_render_queue	*queue;

	queue = render_queue_get();
	if (queue->count == RENDER_QUEUE_CAP)
	{
		fprintf(stderr, "🚨 Render pipe is full (%i) 🚨\n", RENDER_QUEUE_CAP);
		return(false);	// TODO: tmp remove before submit
	}
	queue->elements_3D[queue->count] = element;
	element->render_pos = (int)queue->count;
	queue->count++;
	return (true);
}

void	render_cancel_element(t_element_3D *element)
{
	t_render_queue	*queue;

	queue = render_queue_get();
	if (element->render_pos < 0 || (size_t)element->render_pos >= queue->count)
		return ;
	render_rm(queue->elements_3D, &queue->count, element->render_pos);
}

void	render_flush(void)
{
	t_render_queue	*queue;
	t_mlx			mlx;
	t_clock			clock;

	queue = render_queue_get();
	if (queue->count == 0)
		return ;
	print_warn("Flushing render pipe...\n");

	clock_update_ms();
	clock = *clock_get();
	queue->context = populate_context(queue->context, clock);
	mlx = *view_mlx_get();
	render_display_backgrounds(queue->elements_3D, queue->count, mlx, clock.ms_from_start);
	render_display_and_update_foregrounds(queue->elements_3D, queue->count, mlx, clock.ms_from_start);
	render_callback(queue, clock.ms_from_start);
	render_cleanup(queue, clock.ms_from_start);
	clock_update(false, true);

	print_pass("Render pipe flushed ");
	clock_print();
}

static inline t_render_queue	*render_queue_get(void)
{
	static t_render_queue	render_queue = { 0 };

	return (&render_queue);
}

static inline t_callback_context	populate_context(t_callback_context prev_context, t_clock clock)
{
	return ((t_callback_context)
		{
			.ms_prev_frame = prev_context.ms_curr_frame,
			.ms_curr_frame = clock.ms_from_start,
			.ms_next_frame = clock.ms_from_start + (1000 / FPS),
			.frame = clock.frame + 1
		});
}
