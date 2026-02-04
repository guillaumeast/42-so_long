#include "libft.h"
#include "map_priv.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static bool	read_map(t_buff *buff, char *map_path);
static bool	check_empty_lines(t_buff *buff);

/*
*	Initializes the map struct to NULL/0 for future free() safety.
*/
void	map_init(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->players = 0;
	map->exits = 0;
}

bool	map_load(t_map *map, char *map_path, t_object *player)
{
	t_buff	buff;

	map_init(map);
	if (!read_map(&buff, map_path))
	{
		fprint_err(true, "Map load failed", " '%s'", map_path);
		return (false);
	}
	if (!check_empty_lines(&buff))
	{
		print_err(false, "Map must not contain empty lines.");
		return (buff_free(&buff), false);
	}
	map->grid = str_split(buff.data, '\n');
	if (!map->grid)
	{
		fprint_err(true, "Map split failed", " '%s'", map_path);
		return (buff_free(&buff), false);
	}
	buff_free(&buff);
	return (map_check(map, player));
}

/*
*	Reads all the map_path file into the given buffer (not NULL terminated).
*	Does NOT print error message.
*/
static bool	read_map(t_buff *buff, char *map_path)
{
	int	map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (false);
	buff_init(buff, 0);
	if (!buff_read_all(buff, map_fd))
		return (close(map_fd), false);
	close(map_fd);
	return (true);
}

/*
*	Checks empty lines before split deletes them.
*	Does NOT print error message.
*/
static bool	check_empty_lines(t_buff *buff)
{
	size_t	i;

	if (buff->data[0] == '\n')
		return (false);
	i = 0;
	while (i < buff->len - 1)
	{
		if (buff->data[i] == '\n' && buff->data[i + 1] == '\n')
			return (false);
		i++;
	}
	return (true);
}

void	map_free(t_map *map)
{
	if (map && map->grid)
		str_array_free(&map->grid);
}
