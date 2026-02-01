#ifndef MAP_PRIV_H
# define MAP_PRIV_H

# include "map.h"

/* --- check.c --- */

void	map_init(t_map *map, t_object *player);

/* --- flood_fill.c --- */

bool	valid_path_exists(t_map *map, t_object *player);

#endif
