#include "libft.h"
#include "map.h"
#include <stdlib.h>
#include <unistd.h>

static void	map_check(t_map *map, t_object *player);
static void	parse_cell(t_map *map, size_t y, size_t x, t_object *player);
static void	map_frexit(t_map *map, const char *message);

// Checks first line, last line and first col walls (and last line len)
void	map_init(t_map *map, t_object *player)
{
	size_t	i;

	map->height = 0;
	map->width = 0;
	map->collectibles = 0;
	map->players = 0;
	map->exits = 0;
	while (map->grid[0][map->width])
		if (map->grid[0][map->width++] != '1')
			map_frexit(map, "⇢ Map must be surrounded by walls");
	while (map->grid[map->height])
		if (map->grid[map->height++][0] != '1')
			map_frexit(map, "⇢ Map must be surrounded by walls");
	i = 1;
	while (map->grid[map->height - 1][i])
		if (map->grid[map->height - 1][i++] != '1')
			map_frexit(map, "⇢ Map must be surrounded by walls");
	if (i != map->width)
		map_frexit(map, "⇢ Map must be a rectangle");
	map_check(map, player);
}

// Checks last col walls, each line len and player/exit/collectibles min count
static void	map_check(t_map *map, t_object *player)
{
	size_t	y;
	size_t	x;

	y = 1;
	while (y < map->height)
	{
		x = 1;
		while (map->grid[y][x])
		{
			parse_cell(map, y, x, player);
			x++;
		}
		if (x != map->width)
			map_frexit(map, "⇢ Map must be a rectangle");
		if (map->grid[y][x - 1] != '1')
			map_frexit(map, "⇢ Map must be surrounded by walls");
		y++;
	}
	if (map->players == 0)
		map_frexit(map, "⇢ Map must contain one player");
	if (map->exits == 0)
		map_frexit(map, "⇢ Map must contain one exit");
	if (map->collectibles == 0)
		map_frexit(map, "⇢ Map must contain at least one collectible");
}

// Checks the cell value and the player/exit max count
static void	parse_cell(t_map *map, size_t y, size_t x, t_object *player)
{
	char	cell;

	cell = map->grid[y][x];
	if (cell == '0' || cell == '1')
		return ;
	else if (cell == 'C')
		map->collectibles++;
	else if (cell == 'P')
	{
		if (map->players > 0)
			map_frexit(map, "⇢ Map must contain only one player");
		player->type = PLAYER;
		player->y = y;
		player->x = x;
		map->grid[y][x] = '0';
		map->players++;
	}
	else if (cell == 'E')
	{
		if (map->exits > 0)
			map_frexit(map, "⇢ Map must contain only one exit");
		map->exits++;
	}
	else
		map_frexit(map, "⇢ Map must contain only '0' '1' 'P' 'E' 'C' chars");
}

static void	map_frexit(t_map *map, const char *message)
{
	if (map && map->grid)
		str_array_free(&map->grid);
	ft_dprintf(STDERR_FILENO, "Error\n%s.\n", message);
	exit(EXIT_FAILURE);
}
