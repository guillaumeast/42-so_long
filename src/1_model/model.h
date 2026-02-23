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

void	model_init(void);
bool	model_load(void);
void	model_free(void);

#endif
