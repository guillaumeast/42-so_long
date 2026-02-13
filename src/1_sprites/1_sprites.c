#include "sprites_priv.h"

void	sprites_init_all(t_sprites *sprites)
{
	sprites_font_init(sprites);
	sprites_hud_init(sprites);
	sprites_map_init(sprites);
	sprites_player_init(sprites);
}

bool	sprites_load_all(void *mlx_ptr, t_sprites *sprites)
{
	if (!mlx_ptr)
		return (false);
	if (!sprites_font_load(mlx_ptr, sprites))
		return (sprites_free_all(mlx_ptr, sprites), false);
	if (!sprites_hud_load(mlx_ptr, sprites))
		return (sprites_free_all(mlx_ptr, sprites), false);
	if (!sprites_map_load(mlx_ptr, sprites))
		return (sprites_free_all(mlx_ptr, sprites), false);
	if (!sprites_player_load(mlx_ptr, sprites))
		return (sprites_free_all(mlx_ptr, sprites), false);
	return (true);
}

void	sprites_free_all(void *mlx_ptr, t_sprites *sprites)
{
	if (!mlx_ptr)
		return ;
	sprites_font_free(mlx_ptr, sprites);
	sprites_hud_free(mlx_ptr, sprites);
	sprites_map_free(mlx_ptr, sprites);
	sprites_player_free(mlx_ptr, sprites);
}
