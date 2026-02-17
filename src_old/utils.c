#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>

size_t	get_time_in_ms(void)
{
	struct timeval	raw;

	if (gettimeofday(&raw, NULL) < 0)
	{
		print_err(true, "gettimeofday() failed");
		return (0);
	}
	return ((size_t)(raw.tv_sec * 1000 + raw.tv_usec / 1000));
}

// George Marsaglia (2003)
// 0 <= ret < max
uint	get_random(uint max)
{
	static unsigned int	seed = 0;
	struct timeval		time;
	unsigned int		limit;

	if (max <= 0)
		return (0);
	if (seed == 0)
	{
		if (gettimeofday(&time, NULL) < 0)
			return (0);
		seed = (unsigned int)(time.tv_sec ^ time.tv_usec);
		if (seed == 0)
			seed = 1;
	}
	limit = UINT_MAX - (UINT_MAX % max);
	while (true)
	{
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		if (seed < limit)
			return (seed % max);
	}
}
