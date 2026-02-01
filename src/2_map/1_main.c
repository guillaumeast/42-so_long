#include "libft.h"
#include "map_priv.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	check_empty_lines(t_buff *buff);
static void	frexit(t_buff *buff, const char *message);

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
	map_init(map, player);
	return (valid_path_exists(map, player));
}

// Checks empty lines before split deletes them
static void	check_empty_lines(t_buff *buff)
{
	size_t	i;

	if (buff->data[0] == '\n')
		frexit(buff, "⇢ Map must not contain empty lines.\n");
	i = 0;
	while (i < buff->len - 1)
	{
		if (buff->data[i] == '\n' && buff->data[i + 1] == '\n')
			frexit(buff, "⇢ Map must not contain empty lines.\n");
		i++;
	}
}

static void	frexit(t_buff *buff, const char *message)
{
	if (buff)
		buff_free(buff);
	ft_dprintf(STDERR_FILENO, "Error\n%s.\n", message);
	exit(EXIT_FAILURE);
}
