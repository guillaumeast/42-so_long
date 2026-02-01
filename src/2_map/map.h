#ifndef MAP_H
# define MAP_H

# include "object.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_map
{
	char	**grid;
	size_t	width;
	size_t	height;
	size_t	collectibles;
	size_t	players;
	size_t	exits;
}	t_map;

bool	map_parse(t_map *map, char *map_path, t_object *player);

#endif
