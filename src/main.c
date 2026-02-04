#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_map		map;
	t_object	player;
	t_game		game;

	if (argc != 2)
	{
		fprint_err(false, "Usage", "%s <map.ber>", argv[0]);
		return (EXIT_FAILURE);
	}
	if (!map_load(&map, argv[1], &player))
		return (EXIT_FAILURE);
	if (!game_launch(&game, &map, &player))
		return (EXIT_FAILURE);
	map_free(&map);
	return (EXIT_SUCCESS);
}
