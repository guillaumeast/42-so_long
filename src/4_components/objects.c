#include "hud.h"

# include "logs.h"

static inline void	obj_hud_bg(t_object *object, t_skin *skins);
static inline void	obj_hud_load(t_object *objects, t_skin *skins);

void	hud_load_objects(t_object *objects, t_skin *skins)
{
	obj_hud_bg(&objects[OBJ_HUD_BG], skins);
	obj_hud_load(&objects[OBJ_HUD_BG], skins);
}

static inline void	obj_hud_bg(t_object *object, t_skin *skins)
{
	object_new(object, 0, 0, skins[SKIN_HUD_BG]);
	print_pass("hud background created\n");
}

static inline void	obj_hud_load(t_object *object, t_skin *skins)
{
	object_new(object, 100, 200, skins[SKIN_HUD_LOAD_FULL]);
	print_pass("hud loading created\n");
}
