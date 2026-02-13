#ifndef SPRITES_H
# define SPRITES_H

# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                  HUD_LEFT                                 */
/* ************************************************************************* */

typedef enum e_sprite_hud_left
{
	SPRITES_HUD_LEFT_BASE,
	SPRITES_HUD_LEFT_COLLEC_1,
	SPRITES_HUD_LEFT_COLLEC_2,
	SPRITES_HUD_LEFT_COLLEC_3,
	SPRITES_HUD_LEFT_COLLEC_4,
	SPRITES_HUD_LEFT_COUNT
}	t_sprite_hud_left;

# define SPRITES_HUD_LEFT_HEIGHT_PX			128
# define SPRITES_HUD_LEFT_WIDTH_PX			135
# define SPRITES_HUD_LEFT_PATH				"sprites/hud/hud_left_x.xpm"
# define SPRITES_HUD_LEFT_PATH_ID_INDEX		21

/* ************************************************************************* */
/*                                  HUD_MID                                  */
/* ************************************************************************* */

typedef enum e_sprite_hud_mid
{
	SPRITES_HUD_MID_BASE,
	SPRITES_HUD_MID_COUNT
}	t_sprite_hud_mid;

# define SPRITES_HUD_MID_HEIGHT_PX			128
# define SPRITES_HUD_MID_WIDTH_PX			500
# define SPRITES_HUD_MID_PATH				"sprites/hud/hud_mid_x.xpm"
# define SPRITES_HUD_MID_PATH_ID_INDEX		20

/* ************************************************************************* */
/*                                 HUD_RIGHT                                 */
/* ************************************************************************* */

typedef enum e_sprite_hud_right
{
	SPRITES_HUD_RIGHT_BASE,
	SPRITES_HUD_RIGHT_COUNT
}	t_sprite_hud_right;

# define SPRITES_HUD_RIGHT_HEIGHT_PX		128
# define SPRITES_HUD_RIGHT_WIDTH_PX			135
# define SPRITES_HUD_RIGHT_PATH				"sprites/hud/hud_right_x.xpm"
# define SPRITES_HUD_RIGHT_PATH_ID_INDEX	22

/* ************************************************************************* */
/*                                  FONT                                     */
/* ************************************************************************* */

# define SPRITES_FONT_HEIGHT_PX				28
# define SPRITES_FONT_WIDTH_PX				16

/* --- LETTERS --- */

# define SPRITES_LETTERS_PATH				"sprites/font/letter_x.xpm"
# define SPRITES_LETTERS_PATH_ID_INDEX		20
# define SPRITES_LETTERS_COUNT				26

/* --- NUMBERS --- */

# define SPRITES_NUMBERS_PATH				"sprites/font/number_x.xpm"
# define SPRITES_NUMBERS_PATH_ID_INDEX		20
# define SPRITES_NUMBERS_COUNT				10

/* ************************************************************************* */
/*                                  PLAYER                                   */
/* ************************************************************************* */

// TODO
# define SPRITES_PLAYER_PLACEHOLDER_PATH	"sprites/player/placeholder.xpm"
// # define SPRITES_PLAYER_IDLE_COUNT			1
// # define SPRITES_PLAYER_RUN_COUNT			1
// # define SPRITES_PLAYER_TAKE_COUNT			1
// # define SPRITES_PLAYER_SHOT_COUNT			1

/* ************************************************************************* */
/*                                   MAP                                     */
/* ************************************************************************* */

# define SPRITES_MAP_HEIGHT_PX				64
# define SPRITES_MAP_WIDTH_PX				64
# define SPRITES_MAP_PATH					"sprites/map/map_x.xpm"
# define SPRITES_MAP_PATH_ID_INDEX			16

/* --- FLOORS --- */

typedef enum e_sprite_map
{
	SPRITES_WALL_TOP_LEFT,		// map_A.xpm
	SPRITES_WALL_TOP,			// map_B.xpm
	SPRITES_WALL_BOT,			// map_C.xpm
	SPRITES_WALL_TOP_RIGHT,		// map_D.xpm
	SPRITES_WALL_LEFT,			// map_E.xpm
	SPRITES_WALL_RIGHT,			// map_F.xpm
	SPRITES_WALL_BOT_LEFT,		// map_G.xpm
	SPRITES_WALL_BOT_RIGHT,		// map_H.xpm
	SPRITES_WALL_BASIC,			// map_I.xpm
	SPRITES_WALL_RANDOM_1,		// map_J.xpm
	SPRITES_WALL_RANDOM_2,		// map_K.xpm
	SPRITES_WALL_RANDOM_3,		// map_L.xpm
	SPRITES_WALL_RANDOM_4,		// map_M.xpm
	SPRITES_WALL_RANDOM_5,		// map_N.xpm
	SPRITES_WALL_RANDOM_6,		// map_O.xpm
	SPRITES_WALL_RANDOM_7,		// map_P.xpm
	SPRITES_FLOOR_BASIC,		// map_Q.xpm
	SPRITES_FLOOR_RANDOM_1,		// map_R.xpm
	SPRITES_FLOOR_RANDOM_2,		// map_S.xpm
	SPRITES_FLOOR_RANDOM_3,		// map_T.xpm
	SPRITES_FLOOR_RANDOM_4,		// map_U.xpm
	SPRITES_FLOOR_RANDOM_5,		// map_V.xpm
	SPRITES_FLOOR_RANDOM_6,		// map_W.xpm
	SPRITES_FLOOR_RANDOM_7,		// map_X.xpm
	SPRITES_FLOOR_RANDOM_8,		// map_Y.xpm
	SPRITES_FLOOR_RANDOM_9,		// map_Z.xpm
	SPRITES_FLOOR_RANDOM_10,	// map_[.xpm
	SPRITES_FLOOR_RANDOM_11,	// map_\.xpm
	SPRITES_FLOOR_RANDOM_12,	// map_].xpm
	SPRITES_COLLEC,				// map_^.xpm
	SPRITES_EXIT_CLOSE,			// map__.xpm
	SPRITES_EXIT_OPEN,			// map_`.xpm
	SPRITES_MAP_COUNT
}	t_sprite_map;

# define SPRITES_FLOOR_FIRST				SPRITES_FLOOR_BASIC
# define SPRITES_FLOOR_LAST					SPRITES_FLOOR_RANDOM_12
# define SPRITES_FLOOR_COUNT				(SPRITES_FLOOR_LAST - SPRITES_FLOOR_FIRST + 1)

# define SPRITES_WALL_FIRST					SPRITES_WALL_BASIC
# define SPRITES_WALL_LAST					SPRITES_WALL_RANDOM_7
# define SPRITES_WALL_COUNT					(SPRITES_WALL_LAST - SPRITES_WALL_FIRST + 1)

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef void	*t_image;

typedef struct s_sprite_array
{
	t_image		*dst_array;
	const char	*base_path;
	size_t		path_id_index;
	size_t		count;
	int			expected_height;
	int			expected_width;
}	t_sprite_array;

typedef struct s_sprite
{
	char	*path;
	int		expected_height;
	int		expected_width;
}	t_sprite;

typedef struct s_sprites
{
	t_image	hud_left[SPRITES_HUD_LEFT_COUNT];
	t_image	hud_mid[SPRITES_HUD_MID_COUNT];
	t_image	hud_right[SPRITES_HUD_RIGHT_COUNT];
	t_image	letters[SPRITES_LETTERS_COUNT];
	t_image	numbers[SPRITES_NUMBERS_COUNT];
	t_image	map[SPRITES_MAP_COUNT];
	t_image	player_placeholder;		// TODO
	// t_image	player_idle_left[SPRITES_PLAYER_IDLE_COUNT];
	// t_image	player_idle_right[SPRITES_PLAYER_IDLE_COUNT];
	// t_image	player_idle_down[SPRITES_PLAYER_IDLE_COUNT];
	// t_image	player_run_up[SPRITES_PLAYER_RUN_COUNT];
	// t_image	player_run_left[SPRITES_PLAYER_RUN_COUNT];
	// t_image	player_run_right[SPRITES_PLAYER_RUN_COUNT];
	// t_image	player_run_down[SPRITES_PLAYER_RUN_COUNT];
	// t_image	player_take_up[SPRITES_PLAYER_TAKE_COUNT];
	// t_image	player_take_left[SPRITES_PLAYER_TAKE_COUNT];
	// t_image	player_take_right[SPRITES_PLAYER_TAKE_COUNT];
	// t_image	player_take_down[SPRITES_PLAYER_TAKE_COUNT];
	// t_image	player_shot_up[SPRITES_PLAYER_SHOT_COUNT];
	// t_image	player_shot_left[SPRITES_PLAYER_SHOT_COUNT];
	// t_image	player_shot_right[SPRITES_PLAYER_SHOT_COUNT];
	// t_image	player_shot_down[SPRITES_PLAYER_SHOT_COUNT];
}	t_sprites;

/* ************************************************************************* */
/*                                 FUNCTIONS                                 */
/* ************************************************************************* */

void	sprites_init_all(t_sprites *sprites);
bool	sprites_load_all(void *mlx_ptr, t_sprites *sprites);
void	sprites_free_all(void *mlx_ptr, t_sprites *sprites);

#endif
