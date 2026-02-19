
#include "size.h"
#include "fps.h"

t_size	size_new_static(int height, int width)
{
	return ((t_size)
		{
			.height = height,
			.width = width,
			.frames_left = 1,
			.width_left = 0,
			.height_left = 0
		});
}

t_size	size_new_dynamic(int height, int width, float factor, int duration_ms)
{
	t_size	size;

	if (factor == 0)
		return (size_new_static(height, width));
	if (duration_ms == 0)
		return (size_new_static(
			(int)((float)height * factor),
			(int)((float)width * factor)));
	size.height_left = (int)((float)height * factor) - height;
	size.width_left = (int)((float)width * factor) - width;
	if (duration_ms < 0)
		size.frames_left = -1;
	else
		size.frames_left = (int)fps_ms_to_frames((size_t)duration_ms);
	return (size);
}

void	size_next(t_size *size)
{
	int	delta_height;
	int	delta_width;

	if (size->frames_left == 0)
		return ;
	if ((size->height <= 0 && size->width <= 0) || (size->height_left == 0 && size->width_left == 0))
	{
		size->frames_left = 0;
		return ;
	}
	if (size->frames_left < 0)
	{
		size->height += size->height_left;
		size->width += size->width_left;
		return ;
	}
	delta_height = size->height_left / size->frames_left;
	delta_width = size->width_left / size->frames_left;
	size->height += delta_height;
	size->width += delta_width;
	size->height_left -= delta_height;
	size->width_left -= delta_width;
	size->frames_left--;
}
