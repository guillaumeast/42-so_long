#include "position.h"
#include "fps.h"

# include <stdio.h>

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

t_position	position_new_dynamic(t_pixel src, t_pixel dst, size_t duration_ms)
{
	t_position	position;

	position.frames_left = fps_ms_to_frames(duration_ms);
	if (position.frames_left < 2 || (dst.y == src.y && dst.x == src.x))
		return (position_new_static(dst.y, dst.x));
	position.y = src.y;
	position.x = src.x;
	position.px_y_left = dst.y - src.y;
	position.px_x_left = dst.x - src.x;
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
	delta.y = position->px_y_left / (int)position->frames_left;
	delta.x = position->px_x_left / (int)position->frames_left;
	position->y += delta.y;
	position->x += delta.x;
	position->px_y_left -= delta.y;
	position->px_x_left -= delta.x;
	position->frames_left--;
}

void	position_print(t_position *position)
{
	fprintf(stderr, "📍 y = %4ipx | x = %4ipx", position->y, position->x);
	if (position->frames_left != 0 && position->frames_left != 1)
		fprintf(stderr, " | y += %ipx | x += %ipx | %zu frames left", position->px_y_left, position->px_x_left, position->frames_left);
	fprintf(stderr, "\n");
}
