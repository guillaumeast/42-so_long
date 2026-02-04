#include "libft.h"
#include "map_priv.h"
#include <stdlib.h>
#include <unistd.h>

# include "logs.h"

static bool	flood_init(t_flood *flood, t_map *map);
static bool	flood_exec(t_flood *flood, t_map *map, size_t y, size_t x);
static void	flood_free(t_flood *flood);

bool	map_has_valid_path(t_map *map, t_object *player)
{
	t_flood	flood;

	print_title("valid_path_exists()");
	print_info("map height = %2zu | width = %2zu\n", map->height, map->width);
	print_info("player starts at [%2zu][%2zu]\n", player->y, player->x);
	if (!flood_init(&flood, map))
		return (false);
	print_title("flood_exec()");
	if (!flood_exec(&flood, map, player->y, player->x))
	{
		print_result("flood_exec() done!");
		if (flood.collectibles != map->collectibles)
			print_err(false, "All collectibles must be reachable\n");
		if (!flood.exit)
			print_err(false, "Exit must be reachable.\n");
		flood_free(&flood);
		return (false);
	}
	print_result("flood_exec() done!");
	flood_free(&flood);
	print_result("valid_path_exists() done!");
	return (true);
}

/*
*	Checks if all collectibles and exit are reachable.
*
*	Does print error message.
*	Does NOT free flood on failure.
*	Does NOT free map on failure.
*
*	WARNING: map must have been loaded with map_load().
*/
static bool	flood_init(t_flood *flood, t_map *map)
{
	size_t	y;

	flood->visited = malloc((map->height + 1) * sizeof * flood->visited);
	if (!flood->visited)
		return (fprint_err(true, "Failed alloc",
		" of %zu bytes", (map->height + 1) * sizeof * flood->visited), false);
	y = 0;
	while (y < map->height)
	{
		flood->visited[y] = malloc(map->width * sizeof ** flood->visited);
		if (!flood->visited[y])
			return (fprint_err(true, "Failed alloc", "of %zu bytes at index %zu"
			, map->width * sizeof ** flood->visited, y), false);
		ft_memset(flood->visited[y], false, map->width);
		y++;
	}
	flood->visited[y] = NULL;
	flood->collectibles = 0;
	flood->exit = false;
	return (true);
}

/*
*	Checks recursively each reachable cell of the map.
*
*	Does NOT print error message.
*	Does NOT free flood on failure.
*	Does NOT free map on failure.
*
*	WARNING: flood must have been initialized with flood_init().
*	WARNING: map must have been loaded with map_load().
*/
static bool	flood_exec(t_flood *flood, t_map *map, size_t y, size_t x)
{
	char	cell;

	if (y >= map->height - 1 || x >= map->width - 1)
	{
		print_warn("flood_exec([%2zu][%2zu]) ⇢ Stopping     ⇢ Out of bound\n", y, x);
		return (false);
	}
	if (flood->visited[y][x])
	{
		print_warn("flood_exec([%2zu][%2zu]) ⇢ Stopping     ⇢ Already visited\n", y, x);
		return (false);
	}
	flood->visited[y][x] = true;
	cell = map->grid[y][x];
	if (cell == '1')
	{
		print_warn("flood_exec([%2zu][%2zu]) ⇢ Stopping     ⇢ Wall\n", y, x);
		return (false);
	}
	else if (cell == 'C')
	{
		flood->collectibles++;
		print_pass("flood_exec([%2zu][%2zu]) ⇢ %sCollectibles ⇢ %2zu%s / %2zu\n", y, x, GREEN, flood->collectibles, GREY, map->collectibles);
	}
	else if (cell == 'E')
	{
		flood->exit = true;
		print_pass("flood_exec([%2zu][%2zu]) ⇢ %sExit found%s\n", y, x, GREEN, NC);
	}
	if (flood->collectibles == map->collectibles && flood->exit)
	{
		print_pass("flood_exec([%2zu][%2zu]) ⇢ %sVALID PATH FOUND!%s\n", y, x, GREEN, NC);
		return (true);
	}
	if (flood_exec(flood, map, y + 1, x) || flood_exec(flood, map, y - 1, x))
		return (true);
	if (flood_exec(flood, map, y, x + 1) || flood_exec(flood, map, y, x - 1))
		return (true);
	return (false);
}

/*
*	Frees each pointer inside the array and the array itself.
*
*	WARNING: does NOT set the given pointer to NULL.
*/
static void	flood_free(t_flood *flood)
{
	size_t	y;

	if (!flood)
		return ;
	y = 0;
	while (flood->visited[y])
		free(flood->visited[y++]);
	free(flood->visited);
}
