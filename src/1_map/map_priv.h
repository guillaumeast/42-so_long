#ifndef MAP_PRIV_H
# define MAP_PRIV_H

# include "so_long.h"

typedef struct s_flood
{
	bool	**visited;
	size_t	collectibles;
	bool	exit;
}	t_flood;

/* ************************************************************************* */
/*                                  CHECK.C                                  */
/* ************************************************************************* */

/*
*	Checks the map validity and populates counters.
*
*	Does print error message.
*	Does NOT free map on failure.
*
*	WARNING: map must have been loaded with map_load().
*/
bool	map_check(t_map *map, t_object *player);

/* ************************************************************************* */
/*                                FLOOD_FILL.C                               */
/* ************************************************************************* */

/*
*	Checks if all collectibles and exit are reachable.
*
*	Does print error message.
*	Does NOT free map on failure.
*
*	WARNING: map must have been loaded with map_load().
*/
bool	map_has_valid_path(t_map *map, t_object *player);

#endif
