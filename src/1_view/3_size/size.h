#ifndef FORM_H
# define FORM_H

# include <stddef.h>

typedef struct s_size
{
	int	height;
	int	width;
	int	height_left;
	int	width_left;
	int	frames_left;
}	t_size;

t_size	size_new_static(int height, int width);
t_size	size_new_dynamic(int height, int width, float factor, int duration_ms);
void	size_next(t_size *size);

#endif
