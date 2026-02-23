#ifndef ANIMATION_H
# define ANIMATION_H

# include "sprite_set.h"
# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                 SETTINGS                                  */
/* ************************************************************************* */

typedef enum	e_animation_id
{
	ANIMATION_HUD_LOADING,	// A
	ANIMATION_COUNT
}	t_animation_id;

# define ANIMATION_QUEUE_CAP	6

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef struct s_animation
{
	t_sprite_set	sprite_set;
	size_t			frame_per_sprite;
	int				current_sprite_index;		// -1 if not rendered, else last rendered sprite
	int				direction;					// +1 = from [0] to [n - 1] | -1 = from [n - 1] to [0]
	int				rendered_frame_count;		// -1 if not rendered, else number of rended frames
	int				total_frame_count;			// -1 for infinite
	bool			rollback;
}	t_animation;

typedef struct s_animation_queue
{
	size_t		offset;
	size_t		count;
	t_animation	animations[ANIMATION_QUEUE_CAP];
} t_animation_queue;

/* ************************************************************************* */
/*                                  PROTOS                                   */
/* ************************************************************************* */

t_animation	animation_new(
	t_sprite_set sprite_set,
	size_t frame_per_sprite,
	int frame_count,
	bool rollback);
t_animation_queue	animation_queue_new(void);
bool				animation_queue_add(
	t_animation_queue *queue,
	t_animation animation);
t_image	animation_get_next_image(t_animation_queue *queue, t_image default_image);

/* ************************************************************************* */
/*                                   MODEL                                   */
/* ************************************************************************* */

# define SPRITES_x_OFSSET_Y_START_PX	0
# define SPRITES_x_OFSSET_Y_END_PX		0
# define SPRITES_x_OFSSET_X_START_PX	0
# define SPRITES_x_OFSSET_X_END_PX		0
# define SPRITES_x_START_FRAME_INDEX	0
# define SPRITES_x_END_FRAME_INDEX		(SPRITES_x_COUNT - 1)
# define SPRITES_x_CYCLE_DURATION_MS	0
# define SPRITES_x_CYCLE_COUNT			0
# define SPRITES_x_LOOP					false
# define SPRITES_x_ROLLBACK				false

#endif
