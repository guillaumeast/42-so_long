#include "hud.h"
#include <stdio.h>

static inline t_skin	skin_hud_bg(void);
static inline t_skin	skin_hud_load(void);
static inline t_skin	skin_hud_xav(void);

bool	hud_skins_load(t_skin *skins)
{
	skins[SKIN_HUD_BG] = skin_hud_bg();
	skins[SKIN_HUD_LOAD] = skin_hud_load();
	skins[SKIN_HUD_LOAD_REVERSE] = skin_new_reversed(skins[SKIN_HUD_LOAD]);
	skins[SKIN_HUD_LOAD_FULL] = skin_join(skins[SKIN_HUD_LOAD], skins[SKIN_HUD_LOAD_REVERSE]);
	skins[SKIN_HUD_XAV] = skin_hud_xav();
	return (skin_check(skins, SKIN_HUD_COUNT));
}

static inline t_skin	skin_hud_bg(void)
{
	return (skin_load(
		SKIN_HUD_BG_FOLDER,
		(t_size){SKIN_HUD_BG_HEIGHT_PX, SKIN_HUD_BG_WIDTH_PX},
		SKIN_HUD_BG_COUNT,
		SKIN_HUD_BG_MS));
}

static inline t_skin	skin_hud_load(void)
{
	return (skin_load(
		SKIN_HUD_LOAD_FOLDER,
		(t_size){SKIN_HUD_LOAD_HEIGHT_PX, SKIN_HUD_LOAD_WIDTH_PX},
		SKIN_HUD_LOAD_COUNT, SKIN_HUD_LOAD_MS));
}

static inline t_skin	skin_hud_xav(void)
{
	return (skin_load(
		SKIN_HUD_XAV_FOLDER,
		(t_size){SKIN_HUD_XAV_HEIGHT_PX, SKIN_HUD_XAV_WIDTH_PX},
		SKIN_HUD_XAV_COUNT, SKIN_HUD_XAV_MS));
}
