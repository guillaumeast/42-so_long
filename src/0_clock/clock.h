#ifndef CLOCK_H
# define CLOCK_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/time.h>
# include <sys/types.h>

/* ************************************************************************* */
/*                                   CLOCK                                   */
/* ************************************************************************* */

// 24 bytes
typedef struct s_clock
{
	uint	ms_raw_start;
	uint	ms_raw_curr;
	uint	ms_from_start;
	uint	tick;
	uint	tps;
	uint	frame;
	uint	fps;
}	t_clock;

/* --- hot_loop.c --- */

t_clock	*clock_get(void);
void	clock_init(void);
void	clock_update(bool tick, bool frame);
void	clock_update_ms(void);

/* --- chill_loop.c --- */

void	clock_update_tick(void);
void	clock_update_frame(void);
void	clock_print(void);

#endif
