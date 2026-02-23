#include "controller.h"
#include <stdlib.h>

void	propagate_init(t_controller *self)
{
	uint	i;

	if (self->handler_init)
		self->handler_init(self);
	i = 0;
	while (i < self->controller_len)
		propagate_init(&self->controllers[i++]);
}

bool	propagate_load(t_controller *self)
{
	uint	i;

	if (self->handler_load)
		if (!self->handler_load(self))
			return (false);
	i = 0;
	while (i < self->controller_len)
		if (!propagate_load(&self->controllers[i++]))
			return (false);
	return (true);
}

void	propagate_free(t_controller *self)
{
	uint	i;

	i = 0;
	while (i < self->controller_len)
		propagate_free(&self->controllers[i++]);
	if (self->handler_free)
		self->handler_free(self);
}

void	propagate_event(t_controller *self, int event)
{
	uint	i;

	i = 0;
	if (self->handler_event)
		self->handler_event(self, event);
	while (i < self->controller_len)
	{
		propagate_event(&self->controllers[i], event);
		i++;
	}
}

void	propagate_frame(t_controller *self, t_clock clock)
{
	uint	i;

	i = 0;
	if (self->handler_frame)
		self->handler_frame(self, clock);
	while (i < self->controller_len)
	{
		propagate_frame(&self->controllers[i], clock);
		i++;
	}
}
