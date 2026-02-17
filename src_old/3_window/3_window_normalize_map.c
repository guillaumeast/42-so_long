#include "so_long.h"

# include <stdio.h>

static inline void	window_normalize_wall(t_map *map, int x, int y);
static inline void	window_randomize_wall(t_map *map, int x, int y);
static inline void	window_randomize_floor(t_map *map, int x, int y);
static inline bool	is_inner_wall(t_map *map, int x, int y);

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

// Always randomize isolated inner walls (borders are not counted)
// Force other inner walls to be basic wall 75% of the time
// Force random walls (except basic wall) to be different from the previous one
static inline void	window_randomize_wall(t_map *map, int x, int y)
{
	static int	last_non_zero = 0;
	int			random;

	if (is_inner_wall(map, x, y - 1) || is_inner_wall(map, x, y + 1)
		|| is_inner_wall(map, x - 1, y) || is_inner_wall(map, x + 1, y))
	{
		while (true)
		{
			random = (int)get_random(SPRITES_WALL_COUNT * 3);
			if (random >= SPRITES_WALL_COUNT)
				random = 0;
			if (random == 0 || random != last_non_zero)
				break ;
		}
	}
	else
	{
		while (true)
		{
			random = (int)get_random(SPRITES_WALL_COUNT - 1);
			random++;
			if (random != last_non_zero)
				break ;
		}
	}
	if (random != 0)
		last_non_zero = random;
	map->grid[y][x] = (char)(SPRITES_WALL_FIRST + random);
}

// Randomizes ~10 % of the floor tiles
// Forces each random floor tile to be different from the previous one
static inline void	window_randomize_floor(t_map *map, int x, int y)
{
	static int	last_non_zero = 0;
	int			random;

	while (true)
	{
		random = (int)get_random(SPRITES_FLOOR_COUNT * 10);
		if (random >= SPRITES_FLOOR_COUNT)
			random = 0;
		if (random == 0 || random != last_non_zero)
			break ;
	}
	if (random != 0)
		last_non_zero = random;
	map->grid[y][x] = (char)(SPRITES_FLOOR_FIRST + random);
}

static inline bool	is_inner_wall(t_map *map, int x, int y)
{
	char	cell;

	if (y <= 0 || y >= map->height - 1)
		return (false);
	if (x <= 0 || x >= map->width - 1)
		return (false);
	cell = map->grid[y][x];
	if (cell == MAP_WALL_CELL)
		return (true);
	if (cell >= SPRITES_WALL_FIRST && cell <= SPRITES_WALL_LAST)
		return (true);
	return (false);
}
