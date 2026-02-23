#ifndef POSITION_H
# define POSITION_H

# include <stddef.h>

typedef struct t_pixel
{
	int	y;
	int	x;
}	t_pixel;

typedef struct s_position
{
	int		y;
	int		x;
	int		px_y_left;
	int		px_x_left;
	size_t	frames_left;
}	t_position;

t_position	position_new_static(int y, int x);
t_position	position_new_dynamic(t_pixel src, t_pixel dst, size_t duration_ms);
void		position_next(t_position *position);
void		position_print(t_position *position);

#endif
