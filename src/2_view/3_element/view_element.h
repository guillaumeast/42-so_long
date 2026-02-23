#ifndef ELEMENT_H
# define ELEMENT_H

# include "view_settings.h"
# include "view_mlx.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

/* ************************************************************************* */
/*                                  ELEMENT                                  */
/* ************************************************************************* */
/*
** [SEE] view_settings.h	=> settings
** [SEE] view_mlx.h			=> graphic api
** [SEE] view_skin.h		=> image loading module
** [>>>] view_element.h		=> (here you are)
** [SEE] view_render.h		=> rendering module
** [SEE] view.h				=> external user api
**
** This is the logic required by the renderer to structure the data efficiently.
** This abstracts low-level render blocks into high_level 3D-like elements.
** This uses atomic t_img from mlx api
*/

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/* 8 bytes.
*  [_0_] [___] int y.
*  [_0_] [___] int x.
*/
typedef struct s_pixel
{
	int y;	// [_0_] [___]
	int	x;	// [_0_] [___]
}	t_pixel;

/* 16 bytes.
*  [REQ] [BOR] t_img mlx_img.
*  [REQ] [___] int y.
*  [REQ] [___] int x.
*/
typedef struct s_fragment
{
	t_img	mlx_img;	// [REQ] [BOR]
	int		y;			// [REQ] [___]
	int		x;			// [REQ] [___]
}	t_fragment;

/* 16 bytes.
*  [_0_] [___] int y_left.
*  [_0_] [___] int x_left.
*  [_0_] [___] uint ms_left.
*  [_0_] [___] uint ms_end.
*/
typedef struct s_speed
{
	int		y_left;		// [_0_] [___]
	int		x_left;		// [_0_] [___]
	uint	ms_left;	// [_0_] [___]
	uint	ms_end;		// [_0_] [___]
}	t_speed;

/* 32 bytes.
*  [_0_] [BOR] t_img *img_array.
*  [_0_] [___] uint img_curr.
*  [_0_] [___] uint img_last.
*  [_0_] [___] uint ms_start.
*  [_0_] [___] uint ms_end.
*  [_0_] [___] uint ms_total.
*/
typedef struct s_animation
{
	t_img	*img_array;	// [_0_] [BOR]
	uint	img_curr;	// [_0_] [___]
	uint	img_last;	// [_0_] [___]
	uint	ms_start;	// [_0_] [___]
	uint	ms_end;		// [_0_] [___]
	uint	ms_total;	// [_0_] [___]
}	t_animation;

/* 64 bytes.
*  [REQ] [___] t_fragment fragment.
*  [_0_] [___] t_speed translation.
*  [_0_] [___] t_animation animation.
*/
typedef struct s_element_2D
{
	t_fragment	fragment;		// [REQ] [___]
	t_speed		translation;	// [_0_] [___]
	t_animation	animation;		// [_0_] [___]
}	t_element_2D;

// 16 bytes
typedef struct s_callback_context
{
	uint	ms_prev_frame;
	uint	ms_curr_frame;
	uint	ms_next_frame;
	uint	frame;
}	t_callback_context;

/* 32 bytes
* [_0_] [BOR] array of pointers to element_2Ds
*/
typedef t_element_2D	*t_backgrounds[BACKGROUND_COUNT];

/* 128 bytes.
*
*  [SEE] render_queue.h
*  [_!_] Following instructions are depending on render_queue implementation details
*
*  [-1_] [___] int pipe_pos.
*  [_0_] [BOR] t_backgrounds backgrounds.
*  [REQ] [___] t_element_2D element_2D.
*  [_0_] [BOR] void* data.
*  [_0_] [___] t_fn_callback each_frame.
*  [_0_] [___] t_fn_callback last_frame.
*/
typedef struct s_element_3D
{
	int				render_pos;		// [-1_] [ - ] -1 if this element is not in the render pipe
	t_element_2D	element_2D;		// [REQ] [ - ] Rendered after backgrounds and before callbacks
	void			*data;			// [_0_] [BOR] given back into callbacks arguments
	bool 			(*on_frame)(const t_callback_context *context, void *data);		// [_0_] [ - ] called back after each frame (included last one)
	bool 			(*on_last)(const t_callback_context *context, void *data);		// [_0_] [ - ] called back only when element is going to be removed from the render pipe.
	t_backgrounds	backgrounds;	// [_0_] [BOR] Rendered first (before element_2D and callbacks)
}	t_element_3D;

typedef bool (*t_fn_callback)(const t_callback_context *context, void *data);

/* ************************************************************************* */
/*                                 USER API                                  */
/* ************************************************************************* */

/*
*  [REQ] [BOR] element to edit.
*  [REQ] [___] y.
*  [REQ] [___] x.
*  [REQ] [BOR] image.
*/
void	element_new(t_element_3D *dst, int y, int x, t_img image);

/*
*  [REQ] [BOR] element to edit.
*  [REQ] [___] total y offset [+-].
*  [REQ] [___] total x offset [+-].
*  [REQ] [___] total duration (ms).
*/
void	element_set_movement(t_element_3D *dst, int total_y, int total_x, uint ms);

/*
*  [REQ] [BOR] element to edit.
*  [REQ] [BOR] img_head.
*  [REQ] [___] count => size of array starting at img_head.
*  [REQ] [___] ms => total duration.
*/
void	element_set_animation(t_element_3D *dst, t_img *img_head, uint count, uint ms);

/*
*  [REQ] [BOR] element to edit.
*  [_0_] [___] each => called after EVERY frame.
*  [_0_] [___] last => called after LAST frame (before element is potentially being removed from the render pipe)
*/
void	element_add_background(t_element_3D *dst, t_element_2D background);

// TODO: comment
void	element_set_callback(t_element_3D *dst, t_fn_callback each, t_fn_callback last, void *data);

// TODO: comment
void	element_next(t_element_2D *element_2D, uint ms_curr);

# endif
