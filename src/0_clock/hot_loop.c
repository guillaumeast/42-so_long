#include "clock.h"

static inline uint	clock_get_ms()
{
	struct timeval	time_start = { 0 };
	struct timeval	time_curr = { 0 };
	long			ms_from_sec;
	long			ms_from_usec;

	if (time_start.tv_sec == 0)
		if (gettimeofday(&time_start, NULL) < 0)
			return (0);	
	if (gettimeofday(&time_curr, NULL) < 0)
		return (0);
	ms_from_sec = (time_curr.tv_sec - time_start.tv_sec) * 1000;
	ms_from_usec = (time_curr.tv_usec - time_start.tv_usec) / 1000;
	return ((uint)(ms_from_sec + ms_from_usec));
}

t_clock	*clock_get(void)
{
	static t_clock	clock;

	return (&clock);
}

void	clock_init(void)
{
	t_clock *clock;

	clock = clock_get();
	*clock = (t_clock){ 0 };
	clock->ms_raw_start = clock_get_ms();
	clock->ms_raw_curr = clock->ms_raw_start;
}

void	clock_update(bool tick, bool frame)
{
	t_clock	*clock;

	clock = clock_get();
	clock->ms_raw_curr = clock_get_ms();
	clock->ms_from_start = clock->ms_raw_curr - clock->ms_raw_start;
	clock->tick += tick;
	clock->tps = (clock->tick * 1000) / clock->ms_from_start;
	clock->frame += frame;
	clock->fps = (clock->frame * 1000) / clock->ms_from_start;
}

void	clock_update_ms(void)
{
	t_clock	*clock;

	clock = clock_get();
	clock->ms_raw_curr = clock_get_ms();
	clock->ms_from_start = clock->ms_raw_curr - clock->ms_raw_start;
	clock->tps = (clock->tick * 1000) / clock->ms_from_start;
	clock->fps = (clock->frame * 1000) / clock->ms_from_start;
}
