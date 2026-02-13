#ifndef MAP_H
# define MAP_H

# include "sprites.h"
# include <stdbool.h>
# include <stddef.h>

# define MAP_FLOOR_CELL			'0'
# define MAP_WALL_CELL			'1'
# define MAP_COLLEC_CELL		'C'
# define MAP_PLAYER_CELL		'P'
# define MAP_EXIT_CELL			'E'

// Numbers of cells of the bonus maps (y axis)
# define MAP_BONUS_HEIGHT_CELL	12
// Numbers of cells of the bonus maps (x axis)
# define MAP_BONUS_WIDTH_CELL	12

typedef struct s_cell
{
	int		y;
	int		x;
}	t_cell;

typedef struct s_map
{
	char	**grid;
	// Numbers of cells of the maps (y axis)
	int		height;
	// Numbers of cells of the maps (x axis)
	int		width;
	t_cell	player;
	t_cell	exit;
	size_t	collectibles_count;
}	t_map;

void	map_init(t_map *map);
bool	map_load(t_map *map, char *map_path);
void	map_free(t_map *map);

#endif
