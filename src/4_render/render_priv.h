#ifndef RENDER_PRIV_H
# define RENDER_PRIV_H

# include "so_long.h"

/* --- 1_basics.c --- */

void	render_string(t_game *game, const char *string, int x);
void	render_number(t_game *game, size_t number, int y, int x);
void	render_image(t_game *game, void *image, int x, int y);

/* --- 3_map.c --- */

void	render_map(t_game *game);
void	render_cell(t_game *game, int y, int x);

#endif
