#ifndef SPRITES_PRIV_H
# define SPRITES_PRIV_H

# include "sprites.h"

/* --- FONT --- */

void	sprites_font_init(t_sprites *sprites);
bool	sprites_font_load(void *mlx_ptr, t_sprites *sprites);
void	sprites_font_free(void *mlx_ptr, t_sprites *sprites);

/* --- HUD --- */

void	sprites_hud_init(t_sprites *sprites);
bool	sprites_hud_load(void *mlx_ptr, t_sprites *sprites);
void	sprites_hud_free(void *mlx_ptr, t_sprites *sprites);

/* --- MAP --- */

void	sprites_map_init(t_sprites *sprites);
bool	sprites_map_load(void *mlx_ptr, t_sprites *sprites);
void	sprites_map_free(void *mlx_ptr, t_sprites *sprites);

/* --- PLAYER --- */

void	sprites_player_init(t_sprites *sprites);
bool	sprites_player_load(void *mlx_ptr, t_sprites *sprites);
void	sprites_player_free(void *mlx_ptr, t_sprites *sprites);

/* --- UTILS --- */

bool	sprites_load_array(void *mlx_ptr, t_sprite_array *sprite_array);
bool	sprites_load(void *mlx_ptr, t_sprite *sprite, t_image *dst);
void	sprites_free(void *mlx_ptr, t_image *image);

#endif
