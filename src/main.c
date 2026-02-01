#include "libft.h"
#include "map.h"
#include <unistd.h>
#include <stdlib.h>

# include "logs.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_object	player;

	// print_start(99, "main()");
	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "Error\n");
		ft_dprintf(STDERR_FILENO, "Usage: %s <map.ber>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (!map_parse(&map, argv[1], &player))
	{
		ft_dprintf(STDERR_FILENO, "Error\nInternal error.\n");
		return (EXIT_FAILURE);
	}
	str_array_free(&map.grid);
	return (EXIT_SUCCESS);
}
