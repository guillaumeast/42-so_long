#include "libft.h"
#include "map_priv.h"
#include <stdlib.h>
#include <unistd.h>

static inline bool	map_flood_init(t_flood *flood, t_map *map);
static bool			map_flood_exec(t_flood *flood, t_map *map, int y, int x);
static inline void	map_flood_free(t_flood *flood);

bool	map_has_valid_path(t_map *map)
{
	t_flood	flood;

	if (!map_flood_init(&flood, map))
		return (false);
	if (!map_flood_exec(&flood, map, map->player.y, map->player.x))
	{
		if (flood.collectibles != map->collectibles_count)
			print_err(false, "All collectibles must be reachable\n");
		if (!flood.exit)
			print_err(false, "Exit must be reachable.\n");
		map_flood_free(&flood);
		return (false);
	}
	map_flood_free(&flood);
	return (true);
}

static inline bool	map_flood_init(t_flood *flood, t_map *map)
{
	int	y;

	flood->visited = malloc((size_t)(map->height + 1) * sizeof * flood->visited);
	if (!flood->visited)
		return (fprint_err(true, "Failed alloc",
		" of %i bytes", (map->height + 1) * (int)sizeof * flood->visited), false);
	y = 0;
	while (y < map->height)
	{
		flood->visited[y] = malloc((size_t)map->width * sizeof ** flood->visited);
		if (!flood->visited[y])
			return (fprint_err(true, "Failed alloc", "of %i bytes at index %i"
			, map->width * (int)sizeof ** flood->visited, y), false);
		ft_memset(flood->visited[y], false, (size_t)map->width);
		y++;
	}
	flood->visited[y] = NULL;
	flood->collectibles = 0;
	flood->exit = false;
	return (true);
}

static bool	map_flood_exec(t_flood *flood, t_map *map, int y, int x)
{
	char	cell;

	if (y >= map->height - 1 || x >= map->width - 1)
		return (false);
	if (flood->visited[y][x])
		return (false);
	flood->visited[y][x] = true;
	cell = map->grid[y][x];
	if (cell == MAP_WALL_CELL)
		return (false);
	else if (cell == MAP_COLLEC_CELL)
		flood->collectibles++;
	else if (cell == MAP_EXIT_CELL)
		flood->exit = true;
	if (flood->collectibles == map->collectibles_count && flood->exit)
		return (true);
	if (map_flood_exec(flood, map, y + 1, x) || map_flood_exec(flood, map, y - 1, x))
		return (true);
	if (map_flood_exec(flood, map, y, x + 1) || map_flood_exec(flood, map, y, x - 1))
		return (true);
	return (false);
}

static inline void	map_flood_free(t_flood *flood)
{
	size_t	y;

	if (!flood)
		return ;
	y = 0;
	while (flood->visited[y])
		free(flood->visited[y++]);
	free(flood->visited);
}
