#ifndef MAP_PRIV_H
# define MAP_PRIV_H

# include "libft.h"
# include "map.h"

typedef struct s_flood
{
	bool	**visited;
	size_t	collectibles;
	bool	exit;
}	t_flood;

/* --- CHECK --- */

bool	map_check(t_map *map);
bool	map_check_empty_lines(t_buff *buff);

/* --- FLOOD-FILL --- */

bool	map_has_valid_path(t_map *map);

#endif
