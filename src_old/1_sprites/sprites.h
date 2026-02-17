#ifndef SPRITES_H
# define SPRITES_H

# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                   MODEL                                   */
/* ************************************************************************* */

/* --- sprite_set --- */

# define SPRITES_x_HEIGHT_PX			0
# define SPRITES_x_WIDTH_PX				0
# define SPRITES_x_PATH					"sprites/x/file_*.xpm"
# define SPRITES_x_PATH_ID_INDEX		15

typedef enum e_sprite_x
{
	SPRITES_x_NAME_1,
	SPRITES_x_NAME_2,
	SPRITES_x_COUNT
}	t_sprite_x;

/* --- animation --- */

# define SPRITES_x_OFSSET_Y_START_PX	0
# define SPRITES_x_OFSSET_Y__END_PX		0
# define SPRITES_x_OFSSET_X_START_PX	0
# define SPRITES_x_OFSSET_X__END_PX		0
# define SPRITES_x_START_FRAME_INDEX	0
# define SPRITES_x_END_FRAME_INDEX		(SPRITES_x_COUNT - 1)
# define SPRITES_x_CYCLE_DURATION_MS	0
# define SPRITES_x_CYCLE_COUNT			0
# define SPRITES_x_LOOP					false
# define SPRITES_x_ROLLBACK				false

/* ************************************************************************* */
/*                                  STRUCT                                   */
/* ************************************************************************* */

typedef void	*t_image;

typedef struct s_sprite_set
{
	const char	*base_path;
	size_t		path_id_index;
	int			height;
	int			width;
	size_t		count;
	t_image		*images;
}	t_sprite_set;

typedef struct s_animation
{
	int				y_start;			// Emplacement au début du cycle : y
	int				y_end;				// Emplacement à la fin du cycle : y
	int				x_start;			// Emplacement au début du cycle : x
	int				x_end;				// Emplacement à la fin du cycle : x
	size_t			start_frame_index;	// Frame de début du cycle
	size_t			end_frame_index;	// Frame de fin du cycle
	size_t			cycles_ms;			// Durée d'un cycle
	size_t			cycles_count;		// Nombre de cycles à effectuer
	bool			loop;				// frame[n - 1] -> frame[0]
	bool			rollback;			// frame[n - 1] -> frame[n - 2]
	t_sprite_set	sprites;
}	t_animation;

typedef enum e_component_type
{
	COMPONENT_HUD_BACKGROUND,
	COMPONENT_HUD_LOADING,
	COMPONENT_COUNT
}	t_component_type;

typedef struct s_component
{
	t_component_type	type;
	t_sprite_set		sprites;
	t_animation			animation;
	bool				is_loaded;
	bool				is_visible;
	bool				is_animated;
	int					y;
	int					x;
}	t_component;

// usage: t_component	components[COMPONENT_COUNT];

/* ************************************************************************* */
/*                              HUD_BACKGROUND                               */
/* ************************************************************************* */

/* --- sprite_set --- */

# define SPRITES_HUD_BACKGROUND_PATH			"sprites/hud/hud_*.xpm"
# define SPRITES_HUD_BACKGROUND_PATH_ID_INDEX	16
# define SPRITES_HUD_BACKGROUND_HEIGHT_PX		917
# define SPRITES_HUD_BACKGROUND_WIDTH_PX		1529

typedef enum e_sprite_hud_bg
{
	SPRITES_HUD_BACKGROUND,
	SPRITES_HUD_BACKGROUND_COUNT
}	t_sprite_hud_bg;

/* ************************************************************************* */
/*                                HUD_LOADING                                */
/* ************************************************************************* */

/* --- sprite_set --- */

# define SPRITES_HUD_LOADING_HEIGHT_PX			11
# define SPRITES_HUD_LOADING_WIDTH_PX			1250
# define SPRITES_HUD_LOADING_PATH				"sprites/hud/loading_*.xpm"
# define SPRITES_HUD_LOADING_PATH_ID_INDEX		20

typedef enum e_sprite_hud_loading
{
	SPRITES_HUD_LOADING_1,
	SPRITES_HUD_LOADING_2,
	SPRITES_HUD_LOADING_3,
	SPRITES_HUD_LOADING_4,
	SPRITES_HUD_LOADING_5,
	SPRITES_HUD_LOADING_6,
	SPRITES_HUD_LOADING_7,
	SPRITES_HUD_LOADING_8,
	SPRITES_HUD_LOADING_9,
	SPRITES_HUD_LOADING_COUNT
}	t_sprite_hud_loading;

/* --- animation --- */

# define SPRITES_HUD_LOADING_OFSSET_Y_START_PX	818
# define SPRITES_HUD_LOADING_OFSSET_Y__END_PX	0
# define SPRITES_HUD_LOADING_OFSSET_X_START_PX	818
# define SPRITES_HUD_LOADING_OFSSET_X__END_PX	0
# define SPRITES_HUD_LOADING_START_FRAME_INDEX	0
# define SPRITES_HUD_LOADING_END_FRAME_INDEX	(SPRITES_HUD_LOADING_COUNT - 1)
# define SPRITES_HUD_LOADING_CYCLE_DURATION_MS	1000
# define SPRITES_HUD_LOADING_CYCLE_COUNT		2
# define SPRITES_HUD_LOADING_LOOP				false
# define SPRITES_HUD_LOADING_ROLLBACK			true

// /* ************************************************************************* */
// /*                                  FONT                                     */
// /* ************************************************************************* */

// # define SPRITES_FONT_HEIGHT_PX					28
// # define SPRITES_FONT_WIDTH_PX					16

// /* --- LETTERS --- */

// # define SPRITES_LETTERS_PATH					"sprites/font/letter_*.xpm"
// # define SPRITES_LETTERS_PATH_ID_INDEX			20
// # define SPRITES_LETTERS_COUNT					26

// /* --- NUMBERS --- */

// # define SPRITES_NUMBERS_PATH					"sprites/font/number_*.xpm"
// # define SPRITES_NUMBERS_PATH_ID_INDEX			20
// # define SPRITES_NUMBERS_COUNT					10

// /* ************************************************************************* */
// /*                                  PLAYER                                   */
// /* ************************************************************************* */

// // TODO
// # define SPRITES_PLAYER_PLACEHOLDER_PATH		"sprites/player/placeholder.xpm"
// // # define SPRITES_PLAYER_IDLE_COUNT			1
// // # define SPRITES_PLAYER_RUN_COUNT			1
// // # define SPRITES_PLAYER_TAKE_COUNT			1
// // # define SPRITES_PLAYER_SHOT_COUNT			1

// /* ************************************************************************* */
// /*                                   MAP                                     */
// /* ************************************************************************* */

// # define SPRITES_MAP_HEIGHT_PX					64
// # define SPRITES_MAP_WIDTH_PX					64
// # define SPRITES_MAP_PATH						"sprites/map/map_*.xpm"
// # define SPRITES_MAP_PATH_ID_INDEX				16

// /* --- FLOORS --- */

// typedef enum e_sprite_map
// {
// 	SPRITES_WALL_TOP_LEFT,		// map_A.xpm
// 	SPRITES_WALL_TOP,			// map_B.xpm
// 	SPRITES_WALL_BOT,			// map_C.xpm
// 	SPRITES_WALL_TOP_RIGHT,		// map_D.xpm
// 	SPRITES_WALL_LEFT,			// map_E.xpm
// 	SPRITES_WALL_RIGHT,			// map_F.xpm
// 	SPRITES_WALL_BOT_LEFT,		// map_G.xpm
// 	SPRITES_WALL_BOT_RIGHT,		// map_H.xpm
// 	SPRITES_WALL_BASIC,			// map_I.xpm
// 	SPRITES_WALL_RANDOM_1,		// map_J.xpm
// 	SPRITES_WALL_RANDOM_2,		// map_K.xpm
// 	SPRITES_WALL_RANDOM_3,		// map_L.xpm
// 	SPRITES_WALL_RANDOM_4,		// map_M.xpm
// 	SPRITES_WALL_RANDOM_5,		// map_N.xpm
// 	SPRITES_WALL_RANDOM_6,		// map_O.xpm
// 	SPRITES_WALL_RANDOM_7,		// map_P.xpm
// 	SPRITES_FLOOR_BASIC,		// map_Q.xpm
// 	SPRITES_FLOOR_RANDOM_1,		// map_R.xpm
// 	SPRITES_FLOOR_RANDOM_2,		// map_S.xpm
// 	SPRITES_FLOOR_RANDOM_3,		// map_T.xpm
// 	SPRITES_FLOOR_RANDOM_4,		// map_U.xpm
// 	SPRITES_FLOOR_RANDOM_5,		// map_V.xpm
// 	SPRITES_FLOOR_RANDOM_6,		// map_W.xpm
// 	SPRITES_FLOOR_RANDOM_7,		// map_X.xpm
// 	SPRITES_FLOOR_RANDOM_8,		// map_Y.xpm
// 	SPRITES_FLOOR_RANDOM_9,		// map_Z.xpm
// 	SPRITES_FLOOR_RANDOM_10,	// map_[.xpm
// 	SPRITES_FLOOR_RANDOM_11,	// map_\.xpm
// 	SPRITES_FLOOR_RANDOM_12,	// map_].xpm
// 	SPRITES_COLLEC,				// map_^.xpm
// 	SPRITES_EXIT_CLOSE,			// map__.xpm
// 	SPRITES_EXIT_OPEN,			// map_`.xpm
// 	SPRITES_MAP_COUNT
// }	t_sprite_map;

// # define SPRITES_FLOOR_FIRST					SPRITES_FLOOR_BASIC
// # define SPRITES_FLOOR_LAST						SPRITES_FLOOR_RANDOM_12
// # define SPRITES_FLOOR_COUNT					(SPRITES_FLOOR_LAST - SPRITES_FLOOR_FIRST + 1)

// # define SPRITES_WALL_FIRST						SPRITES_WALL_BASIC
// # define SPRITES_WALL_LAST						SPRITES_WALL_RANDOM_7
// # define SPRITES_WALL_COUNT						(SPRITES_WALL_LAST - SPRITES_WALL_FIRST + 1)

// /* ************************************************************************* */
// /*                                  TYPES                                    */
// /* ************************************************************************* */


// typedef struct s_sprite_array
// {
// 	t_image		*dst_array;
// 	const char	*base_path;
// 	size_t		path_id_index;
// 	size_t		count;
// 	int			expected_height;
// 	int			expected_width;
// }	t_sprite_array;

// typedef struct s_sprites
// {
// 	// t_image	hud_left[SPRITES_HUD_LEFT_COUNT];
// 	// t_image	hud_mid[SPRITES_HUD_MID_COUNT];
// 	// t_image	hud_right[SPRITES_HUD_RIGHT_COUNT];
// 	t_image	hud_background[SPRITES_HUD_BACKGROUND_COUNT];
// 	t_image	hud_loading[SPRITES_HUD_LOADING_COUNT];
// 	t_image	letters[SPRITES_LETTERS_COUNT];
// 	t_image	numbers[SPRITES_NUMBERS_COUNT];
// 	t_image	map[SPRITES_MAP_COUNT];
// 	t_image	player_placeholder;		// TODO
// 	// t_image	player_idle_left[SPRITES_PLAYER_IDLE_COUNT];
// 	// t_image	player_idle_right[SPRITES_PLAYER_IDLE_COUNT];
// 	// t_image	player_idle_down[SPRITES_PLAYER_IDLE_COUNT];
// 	// t_image	player_run_up[SPRITES_PLAYER_RUN_COUNT];
// 	// t_image	player_run_left[SPRITES_PLAYER_RUN_COUNT];
// 	// t_image	player_run_right[SPRITES_PLAYER_RUN_COUNT];
// 	// t_image	player_run_down[SPRITES_PLAYER_RUN_COUNT];
// 	// t_image	player_take_up[SPRITES_PLAYER_TAKE_COUNT];
// 	// t_image	player_take_left[SPRITES_PLAYER_TAKE_COUNT];
// 	// t_image	player_take_right[SPRITES_PLAYER_TAKE_COUNT];
// 	// t_image	player_take_down[SPRITES_PLAYER_TAKE_COUNT];
// 	// t_image	player_shot_up[SPRITES_PLAYER_SHOT_COUNT];
// 	// t_image	player_shot_left[SPRITES_PLAYER_SHOT_COUNT];
// 	// t_image	player_shot_right[SPRITES_PLAYER_SHOT_COUNT];
// 	// t_image	player_shot_down[SPRITES_PLAYER_SHOT_COUNT];
// }	t_sprites;

#endif
