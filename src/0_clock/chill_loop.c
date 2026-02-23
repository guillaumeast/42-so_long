#include "clock.h"

# include "logs.h"

void	clock_update_tick(void)
{
	t_clock	*clock;

	clock = clock_get();
	clock->tick++;
	clock->tps = (clock->tick * 1000) / clock->ms_from_start;
}

void	clock_update_frame(void)
{
	t_clock	*clock;

	clock = clock_get();
	clock->frame++;
	clock->fps = (clock->frame * 1000) / clock->ms_from_start;
}

void	clock_print(void)
{
	t_clock	*clock;

	clock = clock_get();
	print_info("[ ⏱️ | %u ms | %u ticks (%u/s) | %u frames (%u/s)]\n",
		clock->ms_from_start, clock->tick, clock->tps, clock->frame, clock->fps);
}
