#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                  OBJECTS                                  */
/* ************************************************************************* */

# define MAX_OBJ_COUNT 128

typedef struct s_object
{
	size_t		y;
	size_t		x;
}	t_object;

/* ************************************************************************* */
/*                                    MAP                                    */
/* ************************************************************************* */

typedef struct s_map
{
	char	**grid;
	size_t	width;
	size_t	height;
	size_t	collectibles;
	size_t	players;	// TODO: remove
	size_t	exits;		// TODO: remove
}	t_map;

/*
*	Initializes the map struct to NULL/0 for future free() safety.
*/
void	map_init(t_map *map);

/*
*	Loads the map from map_path and populate both map and player structs.
*
*	Does print error message.
*	Does free map on failure.
*
*	WARNING: map must have been initialized with map_init().
*/
bool	map_load(t_map *map, char *map_path, t_object *player);

/*
*	Frees the map struct.
*
*	WARNING: map must have been initialized with map_init() or map_load().
*/
void	map_free(t_map *map);

/* ************************************************************************* */
/*                                  SPRITES                                  */
/* ************************************************************************* */

# define SPRITE_SIZE 64

typedef enum e_sprite
{
	FLOOR,
	TOP_BOT,
	LEFT_RIGHT,
	WALL,
	COLLEC,
	EXIT_CLOSE,
	EXIT_OPEN,
	PLAYER,
	SPRITE_COUNT
}	t_sprite;

/*
*	Populates the sprites array with NULLs for future free() safety.
*/
void	sprite_init_all(void **sprites);

/*
*	Loads each sprite.
*
*	Does print error message.
*	Does free all sprites on failure.
*
*	WARNING: sprites must have been initialized with sprites_free().
*	WARNING: context must be valid.
*/
bool	sprite_load_all(void **sprites, void *context);

/*
*	Frees all sprites by calling the mlx_destroy_image() function.
*
*	Does NOT free the context pointer.
*
*	WARNING: sprites must have been initialized with sprite_init_all().
*	NOTE: no-op if sprites and/or context ptr are NULL.
*/
void	sprite_free_all(void **sprites, void *context);

/* ************************************************************************* */
/*                                    GAME                                   */
/* ************************************************************************* */

typedef struct s_game
{
	void		*context;
	void		*window;
	void		*sprites[SPRITE_COUNT];
	t_map 		map;
	t_object	player;
	// t_object	exit;						// TODO
	// size_t		collectibles_count;		// TODO
	size_t		moves_count;
}	t_game;

/*
*	Populates the game struct and start rendering the window.
*
*	Does NOT free map and player on failure.
*	On succes, do NOT free map / player directly, use game_free() instead.
*
*	WARNING: map and player must be loaded before calling this function.
*/
bool	game_launch(t_game *game, t_map *map, t_object *player);

// TODO: doc
void	game_free(t_game *game);

/* ************************************************************************* */
/*                                   HOOKS                                   */
/* ************************************************************************* */

# define KEY_PRESS		2
# define KEY_PRESS_MASK	1
# define WINDOW_CLOSE	17

# ifdef __APPLE__
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
#  define KEY_DOWN	125
#  define KEY_UP	126
#  define KEY_SPACE	49
#  define KEY_ESC	53
# else
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_DOWN	65364
#  define KEY_UP	65362
#  define KEY_SPACE	32
#  define KEY_ESC	65307
# endif

// TODO: doc
int	handle_key_press(int event_data, void *param);

int handle_window_close(int event_data, void *param);

/* ************************************************************************* */
/*                                   RENDER                                  */
/* ************************************************************************* */

// TODO: doc
void	render_init(t_game *game);

// TODO: doc
void	render_sprite(t_game *game, t_sprite sprite, size_t y, size_t x);

#endif
