#include "libft.h"
#include "map_priv.h"
#include <stdlib.h>
#include <unistd.h>

static inline bool	map_check_all(t_map *map);
static inline bool	map_check_cell(t_map *map, int y, int x);

bool	map_check(t_map *map)
{
	int	i;

	// Check first line chars
	while (map->grid[0][map->width])
		if (map->grid[0][map->width++] != MAP_WALL_CELL)
			return (print_err(false, "Map must be surrounded by walls"), false);
	// Check first col chars
	while (map->grid[map->height])
		if (map->grid[map->height++][0] != MAP_WALL_CELL)
			return (print_err(false, "Map must be surrounded by walls"), false);
	// Check last line chars
	i = 1;
	while (map->grid[map->height - 1][i])
		if (map->grid[map->height - 1][i++] != MAP_WALL_CELL)
			return (print_err(false, "Map must be surrounded by walls"), false);
	if (i != map->width)
		return (print_err(false, "Map must be a rectangle"), false);
	// Check the rest of the chars
	if (!map_check_all(map))
		return (false);
	return (map_has_valid_path(map));
}

bool	map_check_empty_lines(t_buff *buff)
{
	size_t	i;

	if (buff->len == 0)
	{
		print_err(false, "Map is empty.");
		return (false);
	}
	if (buff->data[0] == '\n')
	{
		print_err(false, "Map must not contain empty lines.");
		return (false);
	}
	i = 0;
	while (i < buff->len - 1)
	{
		if (buff->data[i] == '\n' && buff->data[i + 1] == '\n')
		{
			print_err(false, "Map must not contain empty lines.");
			return (false);
		}
		i++;
	}
	return (true);
}

static inline bool	map_check_all(t_map *map)
{
	int	y;
	int	x;

	y = 1;
	while (y < map->height)
	{
		x = 1;
		while (map->grid[y][x])
		{
			if (!map_check_cell(map, y, x++))
				return (false);
		}
		if (x != map->width)
			return (print_err(false, "Map must be a rectangle"), false);
		if (map->grid[y][x - 1] != MAP_WALL_CELL)
			return (print_err(false, "Map must be surrounded by walls"), false);
		y++;
	}
	if (map->player.x == 0)
		return (print_err(false, "Map must contain 1 player"), false);
	if (map->exit.x == 0)
		return (print_err(false, "Map must contain 1 exit"), false);
	if (map->collectibles_count == 0)
		return (print_err(false, "Map must contain collectible(s)"), false);
	return (true);
}

static inline bool	map_check_cell(t_map *map, int y, int x)
{
	char	cell;

	cell = map->grid[y][x];
	if (cell == MAP_COLLEC_CELL)
		map->collectibles_count++;
	else if (cell == MAP_PLAYER_CELL)
	{
		if (map->player.x != 0)
			return (print_err(false, "Map must contain only 1 player"), false);
		map->player.y = y;
		map->player.x = x;
	}
	else if (cell == MAP_EXIT_CELL)
	{
		if (map->exit.x != 0)
			return (print_err(false, "Map must contain only 1 exit"), false);
		map->exit.y = y;
		map->exit.x = x;
	}
	else if (cell != MAP_FLOOR_CELL && cell != MAP_WALL_CELL)
		return (fprint_err(false, 
		"Map contains invalid char", " '%c'", cell), false);
	return (true);
}
