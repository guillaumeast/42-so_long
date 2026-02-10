#ifndef SPRITE_PRIV_H
# define SPRITE_PRIV_H

# include <stddef.h>

typedef struct s_sprite_load
{
	char		*file_path;
	void		**array;
	size_t		index;
	int			expected_height;
	int			expected_width;
}	t_sprite_load;

#endif
