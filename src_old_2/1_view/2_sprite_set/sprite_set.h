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
	SPRITE_SET_XAV,				// C
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

t_sprite_set	*sprite_set_init(void);
bool			sprite_set_load(void *mlx_ptr);
void			sprite_set_free(void *mlx_ptr);

t_sprite_set	sprite_set_get(t_sprite_set_id sprite_set_id);
t_image			sprite_set_get_image(t_sprite_set_id sprite_set_id, size_t image_id);

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
	SPRITE_HUD_BACKGROUND,	// sprites/A/A
	SPRITE_HUD_BACKGROUND_COUNT
}	t_sprite_hud_bg;

/* ************************************************************************* */
/*                           SPRITE_SET_HUD_LOADING                          */
/* ************************************************************************* */

# define SPRITE_SET_HUD_LOADING_HEIGHT_PX		11
# define SPRITE_SET_HUD_LOADING_WIDTH_PX		1250

typedef enum e_sprite_hud_load
{
	SPRITE_HUD_LOADING_1,	// sprites/B/A
	SPRITE_HUD_LOADING_2,	// sprites/B/B
	SPRITE_HUD_LOADING_3,	// sprites/B/C
	SPRITE_HUD_LOADING_4,	// sprites/B/D
	SPRITE_HUD_LOADING_5,	// sprites/B/E
	SPRITE_HUD_LOADING_6,	// sprites/B/F
	SPRITE_HUD_LOADING_7,	// sprites/B/G
	SPRITE_HUD_LOADING_8,	// sprites/B/H
	SPRITE_HUD_LOADING_9,	// sprites/B/I
	SPRITE_HUD_LOADING_0,	// sprites/B/J
	SPRITE_HUD_LOADING_COUNT
}	t_sprite_hud_load;

/* ************************************************************************* */
/*                               SPRITE_SET_XAV                              */
/* ************************************************************************* */

# define SPRITE_SET_XAV_FULL_HEIGHT_PX		100
# define SPRITE_SET_XAV_FULL_WIDTH_PX		100

typedef enum e_sprite_hud_xav
{
	SPRITE_XAV_DEFAULT,		// sprites/C/A
	SPRITE_XAV_OH,			// sprites/C/B
	SPRITE_XAV_YOU,			// sprites/C/C
	SPRITE_XAV_GREEDY,		// sprites/C/D
	SPRITE_XAV_NO,			// sprites/C/E
	SPRITE_XAV_COUNT
}	t_sprite_hud_xav;

#endif
