#include "animation.h"

t_animation	animation_new(
	t_sprite_set sprite_set,
	size_t frame_per_sprite,
	int frame_count,
	bool rollback
)
{
	return ((t_animation)
		{
			.sprite_set = sprite_set,
			.frame_per_sprite = frame_per_sprite,
			.current_sprite_index = 0,
			.direction = 1,
			.rendered_frame_count = 0,
			.total_frame_count = frame_count,
			.rollback = rollback
		});
}

t_animation_queue	animation_queue_new(void)
{
	return ((t_animation_queue)
	{
		.offset = 0,
		.count = 0
	});
}

bool	animation_queue_add(t_animation_queue *queue, t_animation animation)
{
	int	index;

	if (queue->count == ANIMATION_QUEUE_CAP)
		return (false);
	index = (queue->offset + queue->count) % ANIMATION_QUEUE_CAP;
	queue->animations[index] = animation;
	queue->count++;
	return (true);
}

t_image	animation_get_next_image(t_animation_queue *queue, t_image default_image)
{
	t_animation	*animation;
	t_image		next_image;

	if (queue->count == 0)
		return (default_image);
	animation = &queue->animations[queue->offset];
	next_image = animation->sprite_set.images[animation->current_sprite_index];
	animation->current_sprite_index += animation->direction;
	if (animation->current_sprite_index < 0 ||
		animation->current_sprite_index == (int)animation->sprite_set.count)
	{
		if (animation->rollback)
		{
			animation->current_sprite_index -= 2 * animation->direction;
			animation->direction *= -1;
		}
		else
			animation->current_sprite_index = 0;
	}
	if (++animation->rendered_frame_count == animation->total_frame_count)
	{
		queue->offset = (queue->offset + 1) % ANIMATION_QUEUE_CAP;
		queue->count--;
	}
	return (next_image);
}
