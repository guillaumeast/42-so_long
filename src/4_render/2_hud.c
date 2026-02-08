#include "so_long.h"
#include "render_priv.h"

void	render_hud_init(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->window.width)
	{
		render_image(game, game->sprites[HUD_BACKGROUND], i, 0);
		i++;
	}
	render_string(game, HUD_TITLE, HUD_Y_PAD);
	render_number(game, 0, HUD_Y_PAD, HUD_X_PAD + HUD_TITLE_LEN * LETTER_WIDTH);
}

void	render_hud_update(t_game *game)
{
	render_number
	(
		game,
		game->moves_count,
		HUD_Y_PAD,
		HUD_X_PAD + HUD_TITLE_LEN * LETTER_WIDTH
	);
}
