#include "libft.h"
#include "map_priv.h"
#include <stdlib.h>
#include <unistd.h>

static bool	check_map(t_map *map, t_object *player);
static bool	check_cell(t_map *map, size_t y, size_t x, t_object *player);

bool	map_check(t_map *map, t_object *player)
{
	size_t	i;

	// Check first line chars
	while (map->grid[0][map->width])
		if (map->grid[0][map->width++] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
	// Check first col chars
	while (map->grid[map->height])
		if (map->grid[map->height++][0] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
	// Check last line chars
	i = 1;
	while (map->grid[map->height - 1][i])
		if (map->grid[map->height - 1][i++] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
	if (i != map->width)
		return (print_err(false, "Map must be a rectangle"), false);
	// Check the rest of the chars
	if (!check_map(map, player))
		return (false);
	return (map_has_valid_path(map, player));
}

/*
*	Checks last col walls, each line len and player/exit/collectibles min count.
*	Does print error message.
*	Does NOT free map on failure.
*	WARNING: map must have been loaded with map_load().
*/
static bool	check_map(t_map *map, t_object *player)
{
	size_t	y;
	size_t	x;

	y = 1;
	while (y < map->height)
	{
		x = 1;
		while (map->grid[y][x])
		{
			check_cell(map, y, x, player);
			x++;
		}
		if (x != map->width)
			return (print_err(false, "Map must be a rectangle"), false);
		if (map->grid[y][x - 1] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
		y++;
	}
	if (map->players == 0)
		return (print_err(false, "Map must contain 1 player"), false);
	if (map->exits == 0)
		return (print_err(false, "Map must contain 1 exit"), false);
	if (map->collectibles == 0)
		return (print_err(false, "Map must contain collectible(s)"), false);
	return (true);
}

/*
*	Checks the cell value and the player/exit max count.
*	Does print error message.
*	Does NOT free map on failure.
*	WARNING: map must have been loaded with map_load().
*/
static bool	check_cell(t_map *map, size_t y, size_t x, t_object *player)
{
	char	cell;

	cell = map->grid[y][x];
	if (cell == 'C')
		map->collectibles++;
	else if (cell == 'P')
	{
		if (map->players > 0)
			return (print_err(false, "Map must contain only 1 player"), false);
		player->y = y;
		player->x = x;
		map->grid[y][x] = '0';
		map->players++;
	}
	else if (cell == 'E')
	{
		if (map->exits > 0)
			return (print_err(false, "Map must contain only 1 exit"), false);
		map->exits++;
	}
	else if (cell != '0' && cell != '1')
		return (fprint_err(false, 
		"Map contains invalid char", " '%c'", cell), false);
	return (true);
}
