#ifndef SPRITE_SET_H
# define SPRITE_SET_H

# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

# define SPRITE_SET_PATH		"sprites/x/x.xpm"
# define SPRITE_SET_ID_INDEX	8
# define SPRITE_SET_FILE_INDEX	10

typedef enum	e_sprite_set_id
{
	SPRITE_SET_HUD_BACKGROUND,	// A
	SPRITE_SET_HUD_LOADING,		// B
	SPRITE_SET_COUNT
}	t_sprite_set_id;

typedef void	*t_image;

typedef struct s_sprite_set
{
	t_sprite_set_id	id;
	int				height;
	int				width;
	size_t			count;
	t_image			*images;
}	t_sprite_set;

/* ************************************************************************* */
/*                                  PROTOS                                   */
/* ************************************************************************* */

void	sprite_set_init_all(t_sprite_set (*sprite_sets)[SPRITE_SET_COUNT]);
bool	sprite_set_load_all(void *mlx_ptr, t_sprite_set (*sprite_sets)[SPRITE_SET_COUNT]);
void	sprite_set_free_all(void *mlx_ptr, t_sprite_set (*sprite_sets)[SPRITE_SET_COUNT]);

/* ************************************************************************* */
/*                                   MODEL                                   */
/* ************************************************************************* */

// Path to sprites must be 'sprites/<SET_INDEX>/<FILE_INDEX>.xpm'
//	=> SPRITE_HUD_BACKGROUND is at 'sprites/A/A.xpm'
# define SPRITE_SET_x_HEIGHT_PX			0
# define SPRITE_SET_x_WIDTH_PX			0

typedef enum e_sprite_x
{
	SPRITE_SetName_filename_1,
	SPRITE_SetName_filename_2,
	SPRITES_SetName_COUNT
}	t_sprite_x;

/* ************************************************************************************************************************ */
/*                                                           LIST                                                           */
/* ************************************************************************************************************************ */

/* ************************************************************************* */
/*                         SPRITE_SET_HUD_BACKGROUND                         */
/* ************************************************************************* */

# define SPRITE_SET_HUD_BACKGROUND_HEIGHT_PX	917
# define SPRITE_SET_HUD_BACKGROUND_WIDTH_PX		1529

typedef enum e_sprite_hud_bg
{
	SPRITE_HUD_BACKGROUND,
	SPRITE_HUD_BACKGROUND_COUNT
}	t_sprite_hud_bg;

/* ************************************************************************* */
/*                           SPRITE_SET_HUD_LOADING                          */
/* ************************************************************************* */

# define SPRITE_SET_HUD_LOADING_HEIGHT_PX		11
# define SPRITE_SET_HUD_LOADING_WIDTH_PX		1250

typedef enum e_sprite_hud_load
{
	SPRITE_HUD_LOADING_1,
	SPRITE_HUD_LOADING_2,
	SPRITE_HUD_LOADING_3,
	SPRITE_HUD_LOADING_4,
	SPRITE_HUD_LOADING_5,
	SPRITE_HUD_LOADING_6,
	SPRITE_HUD_LOADING_7,
	SPRITE_HUD_LOADING_8,
	SPRITE_HUD_LOADING_9,
	// SPRITE_HUD_LOADING_0,
	SPRITE_HUD_LOADING_COUNT
}	t_sprite_hud_load;

#endif
