#ifndef HUD_H
# define HUD_H

# include "view.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef enum e_hud_skin
{
	SKIN_HUD_BG,
	SKIN_HUD_LOAD,
	SKIN_HUD_LOAD_REVERSE,
	SKIN_HUD_LOAD_FULL,
	SKIN_HUD_XAV,
	SKIN_HUD_COUNT
}	t_hud_skin;

typedef enum e_hud_object
{
	OBJ_HUD_BG,
	OBJ_HUD_LOAD,
	OBJ_HUD_XAV,
	OBJ_HUD_COUNT
}	t_hud_object;

// 480 bytes
typedef struct s_hud_data
{
	t_skin		skins[SKIN_HUD_COUNT];			// All possible variations of sprites
	t_object	objects[OBJ_HUD_COUNT];	// All borrowed from skins
}	t_hud_data;

/* ************************************************************************* */
/*                                  SPRITES                                  */
/* ************************************************************************* */

# define SKIN_HUD_FOLDER			SPRITES_FOLDER "hud/"

# define SKIN_HUD_BG_FOLDER			SKIN_HUD_FOLDER "background"
# define SKIN_HUD_BG_HEIGHT_PX		WINDOW_HEIGHT_PX
# define SKIN_HUD_BG_WIDTH_PX		WINDOW_WIDTH_PX
# define SKIN_HUD_BG_COUNT			1
# define SKIN_HUD_BG_MS				0

# define SKIN_HUD_LOAD_FOLDER		SKIN_HUD_FOLDER "loading"
# define SKIN_HUD_LOAD_HEIGHT_PX	11
# define SKIN_HUD_LOAD_WIDTH_PX		1250
# define SKIN_HUD_LOAD_COUNT		10
# define SKIN_HUD_LOAD_MS			1000

# define SKIN_HUD_XAV_FOLDER		SKIN_HUD_FOLDER "xav"
# define SKIN_HUD_XAV_HEIGHT_PX		100
# define SKIN_HUD_XAV_WIDTH_PX		100
# define SKIN_HUD_XAV_COUNT			5
# define SKIN_HUD_XAV_MS			5000

/* ************************************************************************* */
/*                               PRIVATE API                                 */
/* ************************************************************************* */

bool	hud_load_skins(t_skin *skins);
void	hud_load_objects(t_object *object, t_skin *skins);

#endif
