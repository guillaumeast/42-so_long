#ifndef VIEW_SKIN_H
# define VIEW_SKIN_H

# include "view_mlx.h"
# include <sys/types.h>

/* ************************************************************************* */
/*                                   SKIN                                    */
/* ************************************************************************* */
/*
** [SEE] view_settings.h	=> settings
** [SEE] view_mlx.h			=> graphic api
** [>>>] view_skin.h		=> (here you are)
** [SEE] view_element.h		=> render element constructor
** [SEE] view_render.h		=> rendering module
** [SEE] view.h				=> external user api
**
** Loader of images using mlx_api.
** Allows minimum allocations by seprating raw sprites from skin variations.
*/

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

// 8 bytes
typedef struct s_size
{
	int	height;
	int	width;
}	t_size;

// 24 bytes
typedef struct s_sprites
{
	t_img	*images;
	t_size	size;
	uint	count;
}	t_sprites;

// 32 bytes
typedef struct s_skin
{
	t_sprites	sprites;
	uint		ms_anim;
	bool		own_array;
	bool		own_imgs;
}	t_skin;

/* ************************************************************************* */
/*                             TODO: make priv                               */
/* ************************************************************************* */

// [ ! ] caller must free the skin with skin_free() or skin_free_all()
// [ i ] caller must check skins validity with skin_check()
// [ i ] folder_name is between sprites dir and files ⇢ 'sprites/<FOLDER_NAME>/*.xpm'
// [ i ] Default: frame_start = 0 | frame_end = sprites.count - 1 | default_ms = 1000
t_sprites	sprites_load(const char *folder_path, t_size size, uint count);

// If at least one skin is invalid, frees all skins and return false
bool		sprites_check(t_sprites *sprites, uint count);

// Free all sprites of an array (array itself is not free'd)
void		sprites_free_all(t_sprites *sprites, uint count);
t_sprites	sprites_free(t_sprites sprites);

/* ************************************************************************* */
/*                                 USER API                                  */
/* ************************************************************************* */

t_skin	skin_load(const char *folder_path, t_size size, uint count, uint ms);
bool	skin_check(t_skin *skins, uint count);
t_skin	skin_dup(t_skin skin);
t_skin	skin_join(t_skin skin_1, t_skin skin_2);
t_skin	skin_new_static(t_skin skin);
t_skin	skin_new_anim(t_skin skin, uint ms);
t_skin	skin_new_custom(t_skin skin, uint img_start, uint img_end, uint ms);
t_skin	skin_new_reversed(t_skin skin);
t_skin	skin_free(t_skin skin);
void	skin_free_all(t_skin *skins, uint count);

#endif
