#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

void	map_init(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

void	map_free(t_map *map)
{
	if (map->grid)
		str_array_free(&map->grid);
	map_init(map);
}
