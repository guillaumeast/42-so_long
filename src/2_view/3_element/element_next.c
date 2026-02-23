#include "view_element.h"

static inline void	position_next(t_element_2D *element_2D, uint ms_curr);
static inline void	animation_next(t_element_2D *element_2D, uint ms_curr);

void	element_next(t_element_2D *element_2D, uint ms_curr)
{
	position_next(element_2D, ms_curr);
	animation_next(element_2D, ms_curr);
}

static inline void	position_next(t_element_2D *element_2D, uint ms_curr)
{
	int	delta_y;
	int	delta_x;
	int	ms_since_last;

	ms_since_last = (int)element_2D->translation.ms_left - ((int)element_2D->translation.ms_end - (int)ms_curr);
	delta_y = (element_2D->translation.y_left * ms_since_last) / (int)element_2D->translation.ms_left;
	delta_x = (element_2D->translation.x_left * ms_since_last) / (int)element_2D->translation.ms_left;
	element_2D->fragment.y += delta_y;
	element_2D->fragment.x += delta_x;
	element_2D->translation.y_left -= delta_y;
	element_2D->translation.x_left -= delta_x;
	element_2D->translation.ms_left = element_2D->translation.ms_end - ms_curr;
}

static inline void	animation_next(t_element_2D *element_2D, uint ms_curr)
{
	if (element_2D->animation.ms_total == 0)
		return ;
	element_2D->animation.img_curr = ((element_2D->animation.img_last) * (ms_curr - element_2D->animation.ms_start)) / element_2D->animation.ms_total;
	element_2D->fragment.mlx_img = element_2D->animation.img_array[element_2D->animation.img_curr];
}
