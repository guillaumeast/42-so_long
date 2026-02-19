#ifndef DATA_H
# define DATA_H

# include "model.h"
# include "view.h"
# include "controller.h"

typedef struct	s_data
{
	void		*mlx_ptr;		// Owned
	t_model		model;			// Borrowed
	t_view		view;			// Borrowed
	t_control	control;		// Borrowed
}	t_data;

t_data	data_init(void);
bool	data_load(t_data *data);
void	data_free(t_data *data);

#endif
