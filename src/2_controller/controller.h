#ifndef CONTROLLER_H
# define CONTROLLER_H

# include "object.h"

typedef enum e_controller_id
{
	CONTROLLER_HUD,
	CONTROLLER_COUNT
}	t_controller_id;

typedef struct s_controller
{
	struct s_controller	*controllers;	// Owned
	size_t				controller_len;
	size_t				controller_cap;
	t_object			*objects;		// Owned
	size_t				objects_len;
	size_t				objects_cap;
	bool				(*handler)(int event_data, void *param);	// handler called when an event occured
}	t_controller;

typedef struct s_control
{
	t_controller	controllers[CONTROLLER_COUNT];
}	t_control;

t_control	control_init(void);
bool		control_load(t_control *control, void *param);
void		control_free(t_control *control);

#endif
