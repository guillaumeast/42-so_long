#ifndef CONTROLLER_H
# define CONTROLLER_H

# include "clock.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

/* ************************************************************************* */
/*                                 CONTROLLER                                */
/* ************************************************************************* */
/*
*/

/* ************************************************************************* */
/*                                  SETTINGS                                 */
/* ************************************************************************* */

# define KEY_PRESS				2
# define KEY_PRESS_MASK			1
# define WINDOW_CLOSE			17

# ifdef __APPLE__
#  define KEY_LEFT				123
#  define KEY_RIGHT				124
#  define KEY_DOWN				125
#  define KEY_UP				126
#  define KEY_SPACE				49
#  define KEY_ESC				53
# else
#  define KEY_LEFT				65361
#  define KEY_RIGHT				65363
#  define KEY_DOWN				65364
#  define KEY_UP				65362
#  define KEY_SPACE				32
#  define KEY_ESC				65307
# endif

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

// 64 bytes
typedef struct s_controller
{
	void				*data;
	struct s_controller	*controllers;
	uint				controller_len;
	uint				controller_cap;
	void				(*handler_init)(struct s_controller *self);					// [REQ]
	bool				(*handler_load)(struct s_controller *self);					// [REQ]
	void				(*handler_free)(struct s_controller *self);					// [REQ]
	int					(*handler_event)(struct s_controller *self, int event);		// [_?_]
	int					(*handler_frame)(struct s_controller *self, t_clock clock);	// [_?_]
}	t_controller;

typedef void	(*t_fn_handler_init)(t_controller *self);
typedef bool	(*t_fn_handler_load)(t_controller *self);
typedef void	(*t_fn_handler_free)(t_controller *self);
typedef int		(*t_fn_handler_event)(t_controller *self, int event);
typedef int		(*t_fn_handler_frame)(t_controller *self, t_clock clock);

/* ************************************************************************* */
/*                               FRAMEWORK API                               */
/* ************************************************************************* */

void	controller_init(void);
bool	controller_load(void);
void	controller_set_handlers(void);
void	controller_free(void);

/* ************************************************************************* */
/*                                 USER API                                  */
/* ************************************************************************* */

// Returns the main controller
t_controller	*controller_get(void);
void			controller_play(void);
void			controller_stop(void);

#endif
