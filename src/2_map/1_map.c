#include "libft.h"
#include "map_priv.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static inline bool	map_read(t_buff *buff, char *map_path);

void	map_init(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles_count = 0;
	map->player.x = 0;
	map->player.y = 0;
	map->exit.x = 0;
	map->exit.y = 0;
}

bool	map_load(t_map *map, char *map_path)
{
	t_buff	buff;

	if (!map_read(&buff, map_path))
		return (false);
	if (!map_check_empty_lines(&buff))
		return (buff_free(&buff), false);
	if (!buff_append(&buff, "\0", 1))
	{
		fprint_err(true, "Unable to NULL terminate map", " '%s'", map_path);
		return (buff_free(&buff), false);
	}
	map->grid = str_split(buff.data, '\n');
	if (!map->grid)
	{
		fprint_err(true, "Map split failed", " '%s'", map_path);
		return (buff_free(&buff), false);
	}
	buff_free(&buff);
	if (!map_check(map))
		return (false);
	return (true);
}

static inline bool	map_read(t_buff *buff, char *map_path)
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

void	map_free(t_map *map)
{
	if (map->grid)
		str_array_free(&map->grid);
	map_init(map);
}
