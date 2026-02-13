#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/time.h>

size_t	get_time_in_ms(t_game *game)
{
	struct timeval	raw;

	if (gettimeofday(&raw, NULL) < 0)
	{
		mlx_loop_end(game->mlx_ptr);
		game_free(game);
		print_err(true, "gettimeofday() failed");
		exit(EXIT_FAILURE);
	}
	return ((size_t)(raw.tv_sec * 1000 + raw.tv_usec / 1000));
}

// George Marsaglia (2003)
// 0 <= ret < max
uint	get_random(uint max)
{
	static unsigned int	seed = 0;
	static uint			last = 0;
	struct timeval		time;

	if (max <= 0)
		return (0);
	if (seed == 0)
	{
		if (gettimeofday(&time, NULL) < 0)
			return (0);
		seed = (unsigned int)(time.tv_sec ^ time.tv_usec);
	}
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	while (seed != 0 && seed == last)
		seed = get_random(max);
	last = seed;
	return (seed % max);
}
