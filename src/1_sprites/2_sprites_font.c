#include "sprites_priv.h"

void	sprites_font_init(t_sprites *sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_LETTERS_COUNT)
		sprites->letters[i++] = NULL;
	i = 0;
	while (i < SPRITES_NUMBERS_COUNT)
		sprites->numbers[i++] = NULL;
}

bool	sprites_font_load(void *mlx_ptr, t_sprites *sprites)
{
	t_sprite_array	sprite_array;

	sprite_array.dst_array = sprites->letters;
	sprite_array.base_path = SPRITES_LETTERS_PATH;
	sprite_array.path_id_index = SPRITES_LETTERS_PATH_ID_INDEX;
	sprite_array.count = SPRITES_LETTERS_COUNT;
	sprite_array.expected_height = SPRITES_FONT_HEIGHT_PX;
	sprite_array.expected_width = SPRITES_FONT_WIDTH_PX;
	if (!sprites_load_array(mlx_ptr, &sprite_array))
		return (false);
	sprite_array.dst_array = sprites->numbers;
	sprite_array.base_path = SPRITES_NUMBERS_PATH;
	sprite_array.path_id_index = SPRITES_NUMBERS_PATH_ID_INDEX;
	sprite_array.count = SPRITES_NUMBERS_COUNT;
	sprite_array.expected_height = SPRITES_FONT_HEIGHT_PX;
	sprite_array.expected_width = SPRITES_FONT_WIDTH_PX;
	return (sprites_load_array(mlx_ptr, &sprite_array));
}

void	sprites_font_free(void *mlx_ptr, t_sprites *sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_LETTERS_COUNT && sprites->letters[i])
		sprites_free(mlx_ptr, &sprites->letters[i++]);
	i = 0;
	while (i < SPRITES_NUMBERS_COUNT && sprites->numbers[i])
		sprites_free(mlx_ptr, &sprites->numbers[i++]);
}
