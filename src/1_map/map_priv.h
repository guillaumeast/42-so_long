#ifndef MAP_PRIV_H
# define MAP_PRIV_H

# include "so_long.h"

typedef struct s_flood
{
	bool	**visited;
	size_t	collectibles;
	bool	exit;
}	t_flood;

/* --- check.c --- */

bool	map_check(t_game *game);

/* --- flood_fill.c --- */

bool	map_has_valid_path(t_game *game);

#endif
