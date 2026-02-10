#include "libft.h"
#include "map_priv.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static inline bool	read_map(t_buff *buff, char *map_path);
static inline void	normalize_map(t_game *game);
static inline void	normalize_cell(t_game *game, int x, int y);
static inline void	normalize_wall(t_game *game, int x, int y, char cell);

bool	map_load(t_game *game, char *map_path)
{
	t_buff	buff;

	if (!read_map(&buff, map_path))
		return (false);
	if (!check_empty_lines(&buff))
		return (buff_free(&buff), false);
	if (!buff_append(&buff, "\0", 1))
	{
		fprint_err(true, "Unable to NULL terminate map", " '%s'", map_path);
		return (buff_free(&buff), false);
	}
	game->map.grid = str_split(buff.data, '\n');
	if (!game->map.grid)
	{
		fprint_err(true, "Map split failed", " '%s'", map_path);
		return (buff_free(&buff), false);
	}
	buff_free(&buff);
	if (!map_check(game))
		return (false);
	normalize_map(game);
	return (true);
}

static inline bool	read_map(t_buff *buff, char *map_path)
{
	int	map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		fprint_err(true, "Unable to open map", " '%s'", map_path);
		return (false);
	}
	buff_init(buff, 0);
	if (!buff_read_all(buff, map_fd))
	{
		fprint_err(true, "Unable to read map", " '%s'", map_path);
		close(map_fd);
		return (false);
	}
	close(map_fd);
	return (true);
}

static inline void	normalize_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			normalize_cell(game, x, y);
			x++;
		}
		y++;
	}
}

static inline void	normalize_cell(t_game *game, int x, int y)
{
	char	cell;

	cell = game->map.grid[y][x];
	if (cell == FLOOR_CELL)
		game->map.grid[y][x] = FLOOR;
	else if (cell == COLLEC_CELL)
		game->map.grid[y][x] = COLLEC;
	else if (cell == EXIT_CELL)
		game->map.grid[y][x] = EXIT_CLOSE;
	else if (cell == PLAYER_CELL)
		game->map.grid[y][x] = PLAYER;
	else
		normalize_wall(game, x, y, cell);
}

static inline void	normalize_wall(t_game *game, int x, int y, char cell)
{
	if (cell == WALL_CELL && x == 0 && y != game->map.height - 1)
		game->map.grid[y][x] = WALL_LEFT;
	else if (cell == WALL_CELL && x == 0 && y == game->map.height - 1)
		game->map.grid[y][x] = WALL_BOT_LEFT;
	else if (cell == WALL_CELL && x == game->map.width - 1 && y != game->map.height - 1)
		game->map.grid[y][x] = WALL_RIGHT;
	else if (cell == WALL_CELL && x == game->map.width - 1 && y == game->map.height - 1)
		game->map.grid[y][x] = WALL_BOT_RIGHT;
	else if (cell == WALL_CELL && y == 0 && x == 1)
		game->map.grid[y][x] = WALL_TOP_LEFT;
	else if (cell == WALL_CELL && y == 0 && x == game->map.width - 2)
		game->map.grid[y][x] = WALL_TOP_RIGHT;
	else if (cell == WALL_CELL && (y == 0 || y == game->map.height - 1))
		game->map.grid[y][x] = WALL_TOP_BOT;
	else if (cell == WALL_CELL)
		game->map.grid[y][x] = WALL;
}
