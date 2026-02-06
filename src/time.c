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
