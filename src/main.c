#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

# include "logs.h"

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
	{
		fprint_err(false, "Usage", "%s <map.ber>", argv[0]);
		return (EXIT_FAILURE);
	}
	print_start(99, NULL);
	game_init(&game);
	if (!map_load(&game, argv[1]))
		return (EXIT_FAILURE);
	if (!game_launch(&game))
		return (EXIT_FAILURE);
	game_free(&game);
	print_stop();
	return (EXIT_SUCCESS);
}
