#ifndef CONTROLLER_PRIV_H
# define CONTROLLER_PRIV_H

# include "controller.h"

bool	propagate_init(t_controller *controller);
bool	propagate_load(t_controller *controller);
void	propagate_free(t_controller *controller);
void	propagate_event(t_controller *controller, int event);
void	propagate_frame(t_controller *controller, t_clock clock);

#endif
