#include "view_element.h"
#include "clock.h"

# include "logs.h"

void	element_new(t_element_3D *dst, int y, int x, t_img image)
{
	*dst = (t_element_3D){ 0 };
	dst->render_pos = -1;
	dst->element_2D.fragment.mlx_img = image;
	dst->element_2D.fragment.y = y;
	dst->element_2D.fragment.x = x;
	print_info("3D element created at [%i][%i]\n", y, x);
}

void	element_set_movement(t_element_3D *dst, int y, int x, uint ms)
{
	dst->element_2D.translation.y_left = y;
	dst->element_2D.translation.x_left = x;
	dst->element_2D.translation.ms_end = clock_get()->ms_from_start + ms;
}

void	element_set_animation(t_element_3D *dst, t_img *img_head, uint count, uint ms)
{
	dst->element_2D.fragment.mlx_img = *img_head;
	dst->element_2D.animation.img_array = img_head;
	dst->element_2D.animation.img_curr = 0;
	dst->element_2D.animation.img_last = count;
	dst->element_2D.animation.ms_start = clock_get()->ms_from_start;
	dst->element_2D.animation.ms_total = ms;
	dst->element_2D.animation.ms_end = dst->element_2D.animation.ms_start + ms;
}

void	element_add_background(t_element_3D *dst, t_element_2D background)
{
	uint	i;

	i = 0;
	while (dst->backgrounds[i]->fragment.mlx_img && i < BACKGROUND_COUNT)
		i++;
	if (i >= BACKGROUND_COUNT)
		return ;
	*dst->backgrounds[i] = background;
}

void	element_set_callback(t_element_3D *dst, t_fn_callback each, t_fn_callback last, void *data)
{
	dst->on_frame = each;
	dst->on_last = last;
	dst->data = data;
}
