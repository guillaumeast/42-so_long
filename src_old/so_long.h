#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>	// TMP: remove before submit

# include "map.h"
# include "sprites.h"
# include "window.h"
# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                  EVENTS                                   */
/* ************************************************************************* */

# define KEY_PRESS				2
# define KEY_PRESS_MASK			1
# define WINDOW_CLOSE			17

# ifdef __APPLE__
#  define KEY_LEFT				123
#  define KEY_RIGHT				124
#  define KEY_DOWN				125
#  define KEY_UP				126
#  define KEY_SPACE				49
#  define KEY_ESC				53
# else
#  define KEY_LEFT				65361
#  define KEY_RIGHT				65363
#  define KEY_DOWN				65364
#  define KEY_UP				65362
#  define KEY_SPACE				32
#  define KEY_ESC				65307
# endif

/* ************************************************************************* */
/*                                ANIMATIONS                                 */
/* ************************************************************************* */

# define MIN_MS_BETWEEN_MOVES	0

/* ************************************************************************* */
/*                                  STRUCTS                                  */
/* ************************************************************************* */

typedef struct s_game
{
	void		*mlx_ptr;
	t_map 		map;
	t_sprites	sprites;
	t_window	window;
	t_cell		*modified_cells;
	size_t		modified_cells_count;
	int			moves_count;
}	t_game;

/* ************************************************************************* */
/*                                   UTILS                                   */
/* ************************************************************************* */

size_t	get_time_in_ms(void);
uint	get_random(uint max);

/* ************************************************************************* */
/*                                   RENDER                                  */
/* ************************************************************************* */

int		render_frame(t_game *game);
void	add_modified_cell(t_game *game, int y, int x);

/* ************************************************************************* */
/*                                   HOOKS                                   */
/* ************************************************************************* */

int		handle_key_press(int event_data, void *param);
int 	handle_window_close(void *param);

/* ************************************************************************* */
/*                                    GAME                                   */
/* ************************************************************************* */

bool	game_launch(t_game *game, char *map_path);
void	game_win(t_game *game);
void	game_free(t_game *game);

#endif
