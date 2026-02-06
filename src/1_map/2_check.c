#include "libft.h"
#include "map_priv.h"
#include <stdlib.h>
#include <unistd.h>

static bool	check_map(t_game *game);
static bool	check_cell(t_game *game, int y, int x);

bool	map_check(t_game *game)
{
	int	i;

	// Check first line chars
	while (game->map.grid[0][game->map.width])
		if (game->map.grid[0][game->map.width++] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
	// Check first col chars
	while (game->map.grid[game->map.height])
		if (game->map.grid[game->map.height++][0] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
	// Check last line chars
	i = 1;
	while (game->map.grid[game->map.height - 1][i])
		if (game->map.grid[game->map.height - 1][i++] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
	if (i != game->map.width)
		return (print_err(false, "Map must be a rectangle"), false);
	// Check the rest of the chars
	if (!check_map(game))
		return (false);
	return (map_has_valid_path(game));
}

static bool	check_map(t_game *game)
{
	int	y;
	int	x;

	y = 1;
	while (y < game->map.height)
	{
		x = 1;
		while (game->map.grid[y][x])
		{
			if (!check_cell(game, y, x++))
				return (false);
		}
		if (x != game->map.width)
			return (print_err(false, "Map must be a rectangle"), false);
		if (game->map.grid[y][x - 1] != '1')
			return (print_err(false, "Map must be surrounded by walls"), false);
		y++;
	}
	if (game->player.x == 0)
		return (print_err(false, "Map must contain 1 player"), false);
	if (game->exit.x == 0)
		return (print_err(false, "Map must contain 1 exit"), false);
	if (game->collectibles_count == 0)
		return (print_err(false, "Map must contain collectible(s)"), false);
	return (true);
}

static bool	check_cell(t_game *game, int y, int x)
{
	char	cell;

	cell = game->map.grid[y][x];
	if (cell == 'C')
		game->collectibles_count++;
	else if (cell == 'P')
	{
		if (game->player.x != 0)
			return (print_err(false, "Map must contain only 1 player"), false);
		game->player.y = y;
		game->player.x = x;
		game->map.grid[y][x] = '0';
	}
	else if (cell == 'E')
	{
		if (game->exit.x != 0)
			return (print_err(false, "Map must contain only 1 exit"), false);
		game->exit.y = y;
		game->exit.x = x;
	}
	else if (cell != '0' && cell != '1')
		return (fprint_err(false, 
		"Map contains invalid char", " '%c'", cell), false);
	return (true);
}
