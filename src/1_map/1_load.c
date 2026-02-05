#include "libft.h"
#include "map_priv.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

# include "logs.h"

static bool	read_map(t_buff *buff, char *map_path);
static bool	check_empty_lines(t_buff *buff);

bool	map_load(t_game *game, char *map_path)
{
	t_buff	buff;

	print_title("map_load()");
	if (!read_map(&buff, map_path))
		return (false);
	print_pass("map read\n");
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
	print_pass("map splitted\n");
	if (!map_check(game))
		return (false);
	print_pass("map checked\n");
	print_result("map loaded (h = %zu | w = %zu)", game->map.height, game->map.width);
	return (true);
}

static bool	read_map(t_buff *buff, char *map_path)
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

static bool	check_empty_lines(t_buff *buff)
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
