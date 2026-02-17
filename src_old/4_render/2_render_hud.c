#include "so_long.h"
#include "render_priv.h"

static inline void	render_hud_left(t_game *game);
static inline void	render_hud_mid(t_game *game);
static inline void	render_hud_right(t_game *game);

void	render_hud(t_game *game)
{
	render_hud_left(game);
	render_hud_mid(game);
	render_hud_right(game);
}

static inline void	render_hud_left(t_game *game)
{
	static t_sprite_hud_left	last_sprite = SPRITES_HUD_LEFT_COUNT;
	t_sprite_hud_left			current_sprite;

	current_sprite = SPRITES_HUD_LEFT_BASE;
	if (current_sprite == last_sprite)
		return ;
	render_image(
		game,
		game->sprites.hud_left[current_sprite],
		game->window.hud_left_x_pos_px,
		game->window.hud_y_pos_px
	);
	last_sprite = current_sprite;
}

static inline void	render_hud_mid(t_game *game)
{
	static t_sprite_hud_mid	last_sprite = SPRITES_HUD_MID_COUNT;
	t_sprite_hud_mid		current_sprite;

	current_sprite = SPRITES_HUD_MID_BASE;
	if (current_sprite == last_sprite)
		return ;
	render_image(
		game,
		game->sprites.hud_mid[current_sprite],
		game->window.hud_mid_x_pos_px,
		game->window.hud_y_pos_px
	);
	last_sprite = current_sprite;
}

static inline void	render_hud_right(t_game *game)
{
	static t_sprite_hud_right	last_sprite = SPRITES_HUD_RIGHT_COUNT;
	static int					last_moves = -1;
	t_sprite_hud_right			current_sprite;

	current_sprite = SPRITES_HUD_RIGHT_BASE;
	if (current_sprite == last_sprite && last_moves == game->moves_count)
		return ;
	render_image(
		game,
		game->sprites.hud_right[current_sprite],
		game->window.hud_right_x_pos_px,
		game->window.hud_y_pos_px
	);
	render_number(
		game,
		(size_t)game->moves_count,
		game->window.hud_y_pos_px,
		game->window.hud_right_x_pos_px
	);
	last_sprite = current_sprite;
}
