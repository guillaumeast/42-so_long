#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>

# define FLOOR_CELL				'0'
# define WALL_CELL				'1'
# define COLLEC_CELL			'C'
# define PLAYER_CELL			'P'
# define EXIT_CELL				'E'

# define WINDOW_PAD				100
# define PLAYER_PAD				2

# define HUD_HEIGHT				32
# define HUD_TITLE				"DAYS IN JAIL"
# define HUD_TITLE_LEN			13
# define HUD_Y_PAD				2
# define HUD_X_PAD				2

# define LETTER_HEIGHT			28
# define LETTER_WIDTH			16
# define SPRITE_SIZE			64
# define SPRITE_FLOOR			"sprites/floor/floor.xpm"
# define SPRITE_TOP_BOT			"sprites/wall/border_top_bot.xpm"
# define SPRITE_LEFT_RIGHT		"sprites/wall/border_left_right.xpm"
# define SPRITE_WALL			"sprites/wall/wall_dark_2.xpm"
# define SPRITE_COLLEC			"sprites/collectible/collectible.xpm"
# define SPRITE_EXIT_CLOSE		"sprites/exit/exit_close.xpm"
# define SPRITE_EXIT_OPEN		"sprites/exit/exit_open.xpm"
# define SPRITE_PLAYER			"sprites/player/player.xpm"
# define SPRITE_HUD_BACKGROUND	"sprites/font/background.xpm"

# define MIN_MS_BETWEEN_MOVES	0
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

typedef enum e_sprite
{
	FLOOR,
	WALL_TOP_BOT,
	WALL_LEFT_RIGHT,
	WALL,
	COLLEC,
	EXIT_CLOSE,
	EXIT_OPEN,
	PLAYER,
	HUD_BACKGROUND,
	SPRITE_COUNT
}	t_sprite;

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
