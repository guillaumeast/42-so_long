#include "libft.h"
#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	check_empty_lines(t_buff *buff);
static void	map_init(t_map *map);
static void	map_check(t_map *map, t_object *player);
static void	parse_cell(t_map *map, size_t y, size_t x, t_object *player);
static void	frexit(t_map *map, const char *message);

bool	map_parse(t_map *map, char *map_path, t_object *player)
{
	int		map_fd;
	t_buff	buff;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (false);
	buff_init(&buff, 0);
	if (!buff_read_all(&buff, map_fd))
		return (close(map_fd), false);
	close(map_fd);
	check_empty_lines(&buff);
	map->grid = str_split(buff.data, '\n');
	if (!map->grid)
		return (close(map_fd), buff_free(&buff), false);
	buff_free(&buff);
	map_init(map);
	map_check(map, player);
	return (true);
}

// Checks empty lines before split deletes them
static void	check_empty_lines(t_buff *buff)
{
	size_t	i;

	if (buff->data[0] == '\n')
	{
		buff_free(buff);
		frexit(NULL, "⇢ Map must not contain empty lines");
	}
	i = 0;
	while (i < buff->len - 1)
	{
		if (buff->data[i] == '\n' && buff->data[i + 1] == '\n')
		{
			buff_free(buff);
			frexit(NULL, "⇢ Map must not contain empty lines");
		}
		i++;
	}
}

// Checks first line, last line and first col walls (and last line len)
static void	map_init(t_map *map)
{
	size_t	i;

	map->height = 0;
	map->width = 0;
	map->collectibles = 0;
	map->players = 0;
	map->exits = 0;
	while (map->grid[0][map->width])
		if (map->grid[0][map->width++] != '1')
			frexit(map, "⇢ Map must be surrounded by walls");
	while (map->grid[map->height])
		if (map->grid[map->height++][0] != '1')
			frexit(map, "⇢ Map must be surrounded by walls");
	i = 1;
	while (map->grid[map->height - 1][i])
		if (map->grid[map->height - 1][i++] != '1')
			frexit(map, "⇢ Map must be surrounded by walls");
	if (i != map->width)
		frexit(map, "⇢ Map must be a rectangle");
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
			frexit(map, "⇢ Map must be a rectangle");
		if (map->grid[y][x - 1] != '1')
			frexit(map, "⇢ Map must be surrounded by walls");
		y++;
	}
	if (map->players == 0)
		frexit(map, "⇢ Map must contain one player");
	if (map->exits == 0)
		frexit(map, "⇢ Map must contain one exit");
	if (map->collectibles == 0)
		frexit(map, "⇢ Map must contain at least one collectible");
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
			frexit(map, "⇢ Map must contain only one player");
		player->type = PLAYER;
		player->row = y;
		player->col = x;
		map->grid[y][x] = '0';
		map->players++;
	}
	else if (cell == 'E')
	{
		if (map->exits > 0)
			frexit(map, "⇢ Map must contain only one exit");
		map->exits++;
	}
	else
		frexit(map, "⇢ Map must contain only '0' '1' 'P' 'E' 'C' chars");
}

static void	frexit(t_map *map, const char *message)
{
	if (map && map->grid)
		str_array_free(&map->grid);
	ft_dprintf(STDERR_FILENO, "Error\n%s.\n", message);
	exit(EXIT_FAILURE);
}
