#include "so_long.h"

# include <stdio.h>

static inline void	window_normalize_wall(t_map *map, int x, int y);
static inline void	window_randomize_wall(t_map *map, int x, int y);
static inline void	window_randomize_floor(t_map *map, int x, int y);

void	window_normalize_map(t_map *map)
{
	int		y;
	int		x;
	char	cell;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			cell = map->grid[y][x];
			if (cell == MAP_COLLEC_CELL)
				map->grid[y][x] = SPRITES_COLLEC;
			else if (cell == MAP_EXIT_CELL)
				map->grid[y][x] = SPRITES_EXIT_CLOSE;
			else if (cell == MAP_WALL_CELL)
				window_normalize_wall(map, x, y);
			else
				window_randomize_floor(map, x, y);
			x++;
		}
		y++;
	}
}

static inline void	window_normalize_wall(t_map *map, int x, int y)
{
	if (x == 0 && y != map->height - 1)
		map->grid[y][x] = SPRITES_WALL_LEFT;
	else if (x == 0 && y == map->height - 1)
		map->grid[y][x] = SPRITES_WALL_BOT_LEFT;
	else if (x == map->width - 1 && y != map->height - 1)
		map->grid[y][x] = SPRITES_WALL_RIGHT;
	else if (x == map->width - 1 && y == map->height - 1)
		map->grid[y][x] = SPRITES_WALL_BOT_RIGHT;
	else if (y == 0 && x == 1)
		map->grid[y][x] = SPRITES_WALL_TOP_LEFT;
	else if (y == 0 && x == map->width - 2)
		map->grid[y][x] = SPRITES_WALL_TOP_RIGHT;
	else if (y == 0)
		map->grid[y][x] = SPRITES_WALL_TOP;
	else if (y == map->height - 1)
		map->grid[y][x] = SPRITES_WALL_BOT;
	else
		window_randomize_wall(map, x, y);
}

static inline void	window_randomize_wall(t_map *map, int x, int y)
{
	int	random;

	random = (int)get_random(SPRITES_WALL_COUNT * 3);
	if (random >= SPRITES_WALL_COUNT)
		random = 0;
	map->grid[y][x] = (char)(SPRITES_WALL_FIRST + random);
}

// static inline void	window_randomize_wall(t_map *map, int x, int y)
// {
// 	static int	call_number = 0;
// 	int			random;

// 	if (call_number % 4 == 0)
// 		random = (int)get_random(SPRITES_WALL_COUNT);
// 	else
// 		random = 0;
// 	map->grid[y][x] = (char)(SPRITES_WALL_FIRST + random);
// 	call_number++;
// }

static inline void	window_randomize_floor(t_map *map, int x, int y)
{
	static int	call_number = 0;
	int			random;

	if (call_number % 10 == 0)
		random = (int)get_random(SPRITES_FLOOR_COUNT);
	else
		random = 0;
	map->grid[y][x] = (char)(SPRITES_FLOOR_FIRST + random);
	call_number++;
}
