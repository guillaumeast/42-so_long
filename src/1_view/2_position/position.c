#include "position.h"
#include "fps.h"

t_position	position_new_static(int y, int x)
{
	return ((t_position)
		{
			.y = y,
			.x = x,
			.frames_left = 1,
			.px_y_left = 0,
			.px_x_left = 0
		});
}

t_position	position_new_dynamic(t_pixel src, t_pixel dst, int duration_ms)
{
	t_position	position;

	if (duration_ms == 0 || (dst.y == src.y && dst.x == src.x))
		return (position_new_static(dst.y, dst.x));
	position.y = src.y;
	position.x = src.x;
	position.px_y_left = dst.y - src.y;
	position.px_x_left = dst.x - src.x;
	if (position.px_y_left + position.px_x_left == 0)
		position.frames_left = 1;
	else if (duration_ms < 0)
		position.frames_left = -1;
	else
		position.frames_left = (int)fps_ms_to_frames((size_t)duration_ms);
	return (position);
}

void	position_next(t_position *position)
{
	t_pixel	delta;

	if (position->frames_left == 0)
		return ;
	if (position->px_y_left == 0 && position->px_x_left == 0)
	{
		position->frames_left = 0;
		return ;
	}
	if (position->frames_left < 0)
	{
		position->y += position->px_y_left;
		position->x += position->px_x_left;
		return ;
	}
	delta.y = position->px_y_left / position->frames_left;
	delta.x = position->px_x_left / position->frames_left;
	position->y += delta.y;
	position->x += delta.x;
	position->px_y_left -= delta.y;
	position->px_x_left -= delta.x;
	position->frames_left--;
}
