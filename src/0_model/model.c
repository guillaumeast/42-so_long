#include "model.h"
#include <stdlib.h>

t_model	model_init(void)
{
	return ((t_model)
		{
			.map = NULL,
			.player = (t_cell){0, 0},
			.exit = (t_cell){0, 0},
			.collectibles_left = 0,
			.moves = 0,
		});
}

bool	model_load(t_model *model)
{
	(void)model;
	// TODO
	return (true);
}

void	model_free(t_model *model)
{
	if (model->map)
		free(model->map);
	*model = model_init();
}
