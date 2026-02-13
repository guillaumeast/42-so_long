#include "sprites_priv.h"

void	sprites_player_init(t_sprites *sprites)
{
	sprites->player_placeholder = NULL;
}

bool	sprites_player_load(void *mlx_ptr, t_sprites *sprites)
{
	t_sprite	sprite;

	sprite.path = SPRITES_PLAYER_PLACEHOLDER_PATH;
	sprite.expected_height = SPRITES_MAP_HEIGHT_PX;
	sprite.expected_width = SPRITES_MAP_WIDTH_PX;
	return (sprites_load(mlx_ptr, &sprite, &sprites->player_placeholder));
}

void	sprites_player_free(void *mlx_ptr, t_sprites *sprites)
{
	sprites_free(mlx_ptr, &sprites->player_placeholder);
}
