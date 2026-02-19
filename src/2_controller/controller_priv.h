#ifndef CONTROLLER_PRIV_H
# define CONTROLLER_PRIV_H

# include "data.h"

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

bool	handlers_set(void *param);

// CONTROLLER LIST

bool	hud_load(t_controller *controller, t_data *data);

#endif
