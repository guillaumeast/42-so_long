#ifndef VIEW_H
# define VIEW_H

# include "view_skin.h"
# include "view_element.h"
# include <stdbool.h>
# include <sys/types.h>

/* ************************************************************************* */
/*                                    VIEW                                   */
/* ************************************************************************* */
/*
** [SEE] view_settings.h	=> (here you are)
** [SEE] view_mlx.h			=> graphic api
** [SEE] view_skin.h		=> image loading module
** [SEE] view_element.h		=> render element constructor
** [SEE] view_render.h		=> rendering module
** [>>>] view.h				=> (here you are)
**
** Global graphic API.
** Transform loaded images (see view_skin.h).
** Into render-ready elements (see view_render.h).
*/

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/* 160 bytes.
*
*  [SEE] view_element.h
*  [SEE] view_skin.h
*  [_i_] Bridge between render api (t_element_3D) and skin api (t_skin)
*
*  [_0_] [BOR] render element.
*  [_0_] [BOR] current skin.
*  [_0_] [BOR] data given back by callbacks.
*/
typedef struct s_object
{
	t_element_3D	element_3D;	// [REQ] [BOR]
	t_skin			skin;		// [REQ] [BOR]
	void			*data;		// [_0_] [BOR]
}	t_object;

/* ************************************************************************* */
/*                               FRAMEWORK API                               */
/* ************************************************************************* */

void	view_init(void);	
bool	view_load(void);
void	view_flush(void);	// [SEE] view_render.h
void	view_free(void);

/* ************************************************************************* */
/*                                 USER API                                  */
/* ************************************************************************* */

/*
*  [REQ] [BOR] object to edit.
*  [_0_] [___] y position on screen.
*  [_0_] [___] x position on screen.
*  [REQ] [BOR] skin to display.
*/
void	object_new(t_object *object, int pos_y, int pos_x, t_skin skin);

/*
*  [REQ] [BOR] object to edit.
*  [REQ] [___] y => total y offset [+-].
*  [REQ] [___] x => total x offset [+-].
*  [REQ] [___] ms => total duration.
*/
void	object_move_by(t_object *object, int total_y, int total_x, uint ms);

/*
*  [REQ] [BOR] object to edit.
*  [REQ] [___] y => target y position.
*  [REQ] [___] x => target y position.
*  [REQ] [___] ms => total duration.
*/
void	object_move_to(t_object *object, int dst_y, int dst_x, uint ms);

/*
*  [REQ] [BOR] object to edit.
*  [REQ] [BOR] skin to apply.
*/
void	object_apply_skin(t_object *object, t_skin skin);

/*
*  [REQ] [BOR] object to edit.
*  [REQ] [BOR] skin to apply.
*  [REQ] [___] total ms duration.
*/
void	object_apply_skin_ms(t_object *object, t_skin skin, uint ms);

/*
*  [REQ] [BOR] object to edit.
*  [REQ] [___] callback after each frame (see view_render.h).
*  [REQ] [___] callback after last frame (see view_render.h).
*/
void	object_set_callbacks(t_object *object, t_fn_callback on_frame, t_fn_callback on_last);

/*
*  [REQ] [BOR] element to edit.
*  [REQ] [___] background.
*/
void	object_add_background(t_object *dst, t_object *background);

/*
*  [REQ] [BOR] object to add to the pipe (see view_render.h).
*/
bool	object_render(t_object *object);

/*
*  [REQ] [BOR] object to remove from the pipe (see view_render.h).
*/
void	object_cancel_render(t_object *object);

/* ************************************************************************* */
/*                                   TEST                                    */
/* ************************************************************************* */

// 1. Créer une animation du loader qui [charge -> décharge] au lieu de [charge -> vide]
// 2. Load 2x faster than unload
// 3. Faire flotter Xav en boucle sur l'écran du bas

# define EXAMPLE_SKINS_OWN_COUNT	1
# define EXAMPLE_SKINS_BOR_COUNT	1
# define EXAMPLE_ELEMENTS_COUNT	1

typedef struct s_example_data
{
	t_skin			skins_own[EXAMPLE_SKINS_OWN_COUNT];		// Owned
	t_skin			skins_bor[EXAMPLE_SKINS_BOR_COUNT];		// Borrowed
	t_object	elements[EXAMPLE_ELEMENTS_COUNT];		// Borrowed
}	t_example_data;

// 1. Load sprites	=> owned t_img
// 2. Load skins	=> uniquement borrowed from sprites
// 3. Load objects	=> uniquement borrowed from skins

#endif
