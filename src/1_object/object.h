#ifndef OBJECT_H
# define OBJECT_H

# include <stddef.h>

typedef enum e_object_type
{
	PLAYER,
	ENNEMY,
	COLLECTIBLE,
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	size_t			y;
	size_t			x;
}	t_object;

#endif
