#ifndef VIEW_RENDER_H
# define VIEW_RENDER_H

# include "view_element.h"
# include <sys/types.h>

/* ************************************************************************* */
/*                                RENDER_QUEUE                               */
/* ************************************************************************* */
/*
** [SEE] view_settings.h	=> settings
** [SEE] view_mlx.h			=> graphic api
** [SEE] view_skin.h		=> image loading module
** [SEE] view_element.h		=> render element constructor
** [>>>] view_render.h		=> (here you are)
** [SEE] view.h				=> external user api
**
** [ i ] Render rate is caped at FPS frame per second (see view_settings.h).
** 1. Renders up to BACKGROUND_COUNT backgrounds for each element.
** 2. Renders each element by dissassembling it down to fragments.
**    Updates each element (speed / animation).
** 3. Executes callbacks (each / last frame) with context.
** 4. Cleans up render pipe depending on final elements state.
*/

/* ************************************************************************* */
/*                                   TODO                                    */
/* ************************************************************************* */
/*
** TODO:
** backgrounds pipe (splitted when element is added to the pipe)
** cleanup after all callbacks
*/

/* ************************************************************************* */
/*                                 USER API                                  */
/* ************************************************************************* */

/*
*  Add an element to the render pipe.
*  [REQ] [BOR] 3D element.
*/
bool	render_element(t_element_3D *element);

/*
*  Remove an element from the render pipe.
*  [REQ] [BOR] 3D element.
*/
void	render_cancel_element(t_element_3D *element);

/*
*  Flush the render pipe:
*  1. display all backgrounds (no update, no callback)
*  2. display all foregrounds (display ⇢ update speed ⇢ update animation)
*  3. trigger all callbacks (on_each ⇢ on_last)
*  4. cleanup
*/
void	render_flush(void);

#endif
