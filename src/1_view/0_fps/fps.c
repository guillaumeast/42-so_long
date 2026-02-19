#include "fps.h"
#include <sys/time.h>

# include <stdio.h>

// ret > 0
size_t	fps_ms_to_frames(size_t ms)
{
	size_t	ret;

	ret = FPS * ms / 1000;
	if (ret == 0)
		return (1);
	return (ret);
}

// ret > 0
size_t	fps_frames_to_ms(size_t frames)
{
	size_t	ret;

	ret = 1000 / FPS * frames;
	if (ret == 0)
		return (1);
	return (ret);
}

// ret > 0
size_t	fps_time_in_ms(void)
{
	static size_t	start_ms = 0;
	size_t			current_ms;
	size_t			res;
	struct timeval	raw;

	if (gettimeofday(&raw, NULL) < 0)
		return (start_ms);
	current_ms = (size_t)(raw.tv_sec * 1000 + raw.tv_usec / 1000);
	if (start_ms == 0)
	{
		start_ms = current_ms;
		return (1);
	}
	res = current_ms - start_ms;
	return (res);
}

void	fps_update_time(t_time *time)
{
	time->ms = fps_time_in_ms();
	time->frames++;
	time->fps = time->frames * 1000 / time->ms;
}
