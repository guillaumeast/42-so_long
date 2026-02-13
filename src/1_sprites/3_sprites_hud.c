#include "sprites_priv.h"

void	sprites_hud_init(t_sprites *sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_HUD_LEFT_COUNT)
		sprites->hud_left[i++] = NULL;
	i = 0;
	while (i < SPRITES_HUD_MID_COUNT)
		sprites->hud_mid[i++] = NULL;
	i = 0;
	while (i < SPRITES_HUD_RIGHT_COUNT)
		sprites->hud_right[i++] = NULL;
	i = 0;
}

bool	sprites_hud_load(void *mlx_ptr, t_sprites *sprites)
{
	t_sprite_array	sprite_array;

	sprite_array.dst_array = sprites->hud_left;
	sprite_array.base_path = SPRITES_HUD_LEFT_PATH;
	sprite_array.path_id_index = SPRITES_HUD_LEFT_PATH_ID_INDEX;
	sprite_array.count = SPRITES_HUD_LEFT_COUNT;
	sprite_array.expected_height = SPRITES_HUD_LEFT_HEIGHT_PX;
	sprite_array.expected_width = SPRITES_HUD_LEFT_WIDTH_PX;
	if (!sprites_load_array(mlx_ptr, &sprite_array))
		return (false);
	sprite_array.dst_array = sprites->hud_mid;
	sprite_array.base_path = SPRITES_HUD_MID_PATH;
	sprite_array.path_id_index = SPRITES_HUD_MID_PATH_ID_INDEX;
	sprite_array.count = SPRITES_HUD_MID_COUNT;
	sprite_array.expected_height = SPRITES_HUD_MID_HEIGHT_PX;
	sprite_array.expected_width = SPRITES_HUD_MID_WIDTH_PX;
	if (!sprites_load_array(mlx_ptr, &sprite_array))
		return (false);
	sprite_array.dst_array = sprites->hud_right;
	sprite_array.base_path = SPRITES_HUD_RIGHT_PATH;
	sprite_array.path_id_index = SPRITES_HUD_RIGHT_PATH_ID_INDEX;
	sprite_array.count = SPRITES_HUD_RIGHT_COUNT;
	sprite_array.expected_height = SPRITES_HUD_RIGHT_HEIGHT_PX;
	sprite_array.expected_width = SPRITES_HUD_RIGHT_WIDTH_PX;
	return (sprites_load_array(mlx_ptr, &sprite_array));
}

void	sprites_hud_free(void *mlx_ptr, t_sprites *sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_HUD_LEFT_COUNT && sprites->hud_left[i])
		sprites_free(mlx_ptr, &sprites->hud_left[i++]);
	i = 0;
	while (i < SPRITES_HUD_MID_COUNT && sprites->hud_mid[i])
		sprites_free(mlx_ptr, &sprites->hud_mid[i++]);
	i = 0;
	while (i < SPRITES_HUD_RIGHT_COUNT && sprites->hud_right[i])
		sprites_free(mlx_ptr, &sprites->hud_right[i++]);
	i = 0;
}
