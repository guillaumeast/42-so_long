#ifndef MODEL_H
# define MODEL_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_cell
{
	size_t	y;
	size_t	x;
}	t_cell;

typedef struct s_model
{
	char		**map;
	t_cell		player;
	t_cell		exit;
	size_t		collectibles_left;
	size_t		moves;
}	t_model;

t_model	model_init(void);
bool	model_load(t_model *model);
void	model_free(t_model *model);

#endif
