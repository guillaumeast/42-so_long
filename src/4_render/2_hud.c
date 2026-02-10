#include "so_long.h"
#include "render_priv.h"

void	render_hud_init(t_game *game)
{
	render_string(game, HUD_TITLE, HUD_Y_PAD);
	render_number(game, 0, HUD_Y_PAD, HUD_X_PAD + HUD_TITLE_LEN * HUD_FONT_WIDTH);
}

void	render_hud_update(t_game *game)
{
	render_number
	(
		game,
		game->moves_count,
		HUD_Y_PAD,
		HUD_X_PAD + HUD_TITLE_LEN * HUD_FONT_WIDTH
	);
}
