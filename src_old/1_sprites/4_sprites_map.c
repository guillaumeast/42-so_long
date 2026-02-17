#include "sprites_priv.h"

void	sprites_map_init(t_sprites *sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_MAP_COUNT)
		sprites->map[i++] = NULL;
}

bool	sprites_map_load(void *mlx_ptr, t_sprites *sprites)
{
	t_sprite_array	sprite_array;

	sprite_array.dst_array = sprites->map;
	sprite_array.base_path = SPRITES_MAP_PATH;
	sprite_array.path_id_index = SPRITES_MAP_PATH_ID_INDEX;
	sprite_array.count = SPRITES_MAP_COUNT;
	sprite_array.expected_height = SPRITES_MAP_HEIGHT_PX;
	sprite_array.expected_width = SPRITES_MAP_WIDTH_PX;
	return (sprites_load_array(mlx_ptr, &sprite_array));
}

void	sprites_map_free(void *mlx_ptr, t_sprites *sprites)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_MAP_COUNT && sprites->map[i])
		sprites_free(mlx_ptr, &sprites->map[i++]);
}
