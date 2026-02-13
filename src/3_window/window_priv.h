#ifndef WINDOW_PRIV_H
# define WINDOW_PRIV_H

# include "window.h"
# include "map.h"

/* --- window_map_pos.c --- */

bool	window_compute_map_pos(t_window *window, t_map *map);

/* --- window_normalize_map.c --- */

void	window_normalize_map(t_map *map);

#endif
