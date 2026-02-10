#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>

# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                   MAP                                     */
/* ************************************************************************* */

# define FLOOR_CELL				'0'
# define WALL_CELL				'1'
# define COLLEC_CELL			'C'
# define PLAYER_CELL			'P'
# define EXIT_CELL				'E'

/* ************************************************************************* */
/*                                  WINDOW                                   */
/* ************************************************************************* */

# define WINDOW_PAD				100
# define PLAYER_PAD				2

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
int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int mlx_loop_end (void *mlx_ptr);
int	mlx_destroy_display(void *mlx_ptr);
# else
#  define KEY_LEFT				65361
#  define KEY_RIGHT				65363
#  define KEY_DOWN				65364
#  define KEY_UP				65362
#  define KEY_SPACE				32
#  define KEY_ESC				65307
# endif

/* ************************************************************************* */
/*                                    HUD                                    */
/* ************************************************************************* */

# define HUD_HEIGHT				32
# define HUD_TITLE				"DAYS IN JAIL"
# define HUD_TITLE_LEN			13
# define HUD_Y_PAD				2
# define HUD_X_PAD				2
# define HUD_FONT_HEIGHT		28
# define HUD_FONT_WIDTH			16
# define SPRITE_HUD_FONT		"sprites/font/_.xpm"
# define SPRITE_HUD_IDX			13

/* ************************************************************************* */
/*                                  SPRITES                                  */
/* ************************************************************************* */

# define SPRITE_SIZE			64
# define SPRITE_WALL_TOP_LEFT	"sprites/v3/wall/outer/wall_top_left_64.xpm"
# define SPRITE_WALL_TOP_BOT	"sprites/v3/wall/outer/wall_top_bot_64.xpm"
# define SPRITE_WALL_TOP_RIGHT	"sprites/v3/wall/outer/wall_top_right_64.xpm"
# define SPRITE_WALL_LEFT		"sprites/v3/wall/outer/wall_left_64.xpm"
# define SPRITE_WALL_RIGHT		"sprites/v3/wall/outer/wall_right_64.xpm"
# define SPRITE_WALL_BOT_LEFT	"sprites/v3/wall/outer/wall_bot_left_64.xpm"
# define SPRITE_WALL_BOT_RIGHT	"sprites/v3/wall/outer/wall_bot_right_64.xpm"
# define SPRITE_WALL			"sprites/v2/wall/wall_64.xpm"
# define SPRITE_FLOOR			"sprites/v2/floor/floor_64.xpm"
# define SPRITE_COLLEC			"sprites/v2/collectible/collectible_64.xpm"
# define SPRITE_EXIT_CLOSE		"sprites/v2/exit/exit_close_64.xpm"
# define SPRITE_EXIT_OPEN		"sprites/v2/exit/exit_open_64.xpm"
# define SPRITE_PLAYER			"sprites/v2/player/player_idle_64.xpm"
# define SPRITE_PLAYER_COLL_1	"sprites/v2/player/player_collec_1_64.xpm"
# define SPRITE_PLAYER_COLL_2	"sprites/v2/player/player_collec_2_64.xpm"
# define SPRITE_PLAYER_COLL_3	"sprites/v2/player/player_collec_3_64.xpm"

typedef enum e_sprite
{
	WALL_TOP_LEFT,
	WALL_TOP_BOT,
	WALL_TOP_RIGHT,
	WALL_LEFT,
	WALL_RIGHT,
	WALL_BOT_LEFT,
	WALL_BOT_RIGHT,
	WALL,
	FLOOR,
	COLLEC,
	EXIT_CLOSE,
	EXIT_OPEN,
	PLAYER,
	PLAYER_COLLEC_1,
	PLAYER_COLLEC_2,
	PLAYER_COLLEC_3,
	SPRITE_COUNT
}	t_sprite;

/* ************************************************************************* */
/*                                ANIMATIONS                                 */
/* ************************************************************************* */

# define MIN_MS_BETWEEN_MOVES	0

/* ************************************************************************* */
/*                                  STRUCTS                                  */
/* ************************************************************************* */

typedef struct s_cell
{
	int		y;
	int		x;
}	t_cell;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_window
{
	int		height;
	int		width;
	bool	cropped;
	bool	moved;
	int		y_start;
	int		x_start;
	int		y_end;
	int		x_end;
}	t_window;

typedef struct s_game
{
	t_window	window;
	void		*mlx_ptr;
	void		*mlx_win;
	void		*sprites[SPRITE_COUNT];
	void		*letters[26];
	void		*numbers[10];
	t_map 		map;
	t_cell		*modified_cells;
	size_t		modified_cells_count;
	t_cell		player;
	t_cell		exit;
	size_t		collectibles_count;
	size_t		moves_count;
}	t_game;

/* ************************************************************************* */
/*                                   TIME                                    */
/* ************************************************************************* */

size_t	get_time_in_ms(t_game *game);

/* ************************************************************************* */
/*                                    MAP                                    */
/* ************************************************************************* */

void	map_init(t_map *map);
bool	map_load(t_game *game, char *map_path);
void	map_free(t_map *map);

/* ************************************************************************* */
/*                                  SPRITES                                  */
/* ************************************************************************* */

void	sprite_init_all(t_game *game);
bool	sprite_load_all(t_game *game);
void	sprite_free_all(t_game *game);

/* ************************************************************************* */
/*                                  WINDOW                                   */
/* ************************************************************************* */

bool	window_init(t_game *game);
void	window_center(t_game *game, int target_y, int target_x);

/* ************************************************************************* */
/*                                   RENDER                                  */
/* ************************************************************************* */

void	render_hud_init(t_game *game);
void	render_hud_update(t_game *game);
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

void	game_init(t_game *game);
bool	game_launch(t_game *game);
void	game_win(t_game *game);
void	game_free(t_game *game);

#endif
