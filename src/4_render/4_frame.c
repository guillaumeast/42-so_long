#include "so_long.h"
#include "render_priv.h"

static void	render_modified_cells(t_game *game);

int	render_frame(t_game *game)
{
	if (game->window.moved)
		render_map(game);
	else if (game->modified_cells_count > 0)
		render_modified_cells(game);
	return (0);
}

static void	render_modified_cells(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->modified_cells_count)
	{
		render_cell(game, game->modified_cells[i].y, game->modified_cells[i].x);
		i++;
	}
	game->modified_cells_count = 0;
}

void	add_modified_cell(t_game *game, int y, int x)
{
	if (game->window.moved)
		return ;
	game->modified_cells[game->modified_cells_count].y = y;
	game->modified_cells[game->modified_cells_count].x = x;
	game->modified_cells_count++;
}
