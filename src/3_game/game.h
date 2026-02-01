#ifndef GAME_H
# define GAME_H

# include "object.h"
# include "map.h"

typedef struct s_game
{
	t_map 		*map;
	t_object	*player;
	void		*ctx;
	void		*win;
	void		**sprites;
	size_t		moves;
}	t_game;

#endif
