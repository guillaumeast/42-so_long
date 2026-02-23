#include "render_priv.h"
#include "clock.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

# include "logs.h"

void	render_display_backgrounds(t_element_3D **queue, size_t count, t_mlx mlx, uint ms_curr)
{
	uint			i;
	uint			j;
	uint			render_count;
	t_fragment		fragment;

	i = 0;
	render_count = 0;
	while (i < count)
	{
		j = 0;
		while (j < BACKGROUND_COUNT)
		{
			fragment = queue[i]->backgrounds[j]->fragment;
			if (!fragment.mlx_img)
				break ;
			mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win,
				fragment.mlx_img, fragment.x, fragment.y);
			render_count++;
			j++;
		}
		i++;
	}
	clock_update_ms();
	print_pass("🎨 %4u backgrounds rendered (%2u ms)\n", render_count, clock_get()->ms_from_start - ms_curr);
}

void	render_display_and_update_foregrounds(t_element_3D **queue, size_t count, t_mlx mlx, uint ms_curr)
{
	size_t			i;
	t_element_2D	*element_2D;
	t_fragment		fragment;

	i = 0;
	while (i < count)
	{
		element_2D = &queue[i]->element_2D;
		fragment = element_2D->fragment;
		mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win,
			fragment.mlx_img, fragment.x, fragment.y);
		element_next(element_2D, ms_curr);
		i++;
	}
	clock_update_ms();
	print_pass("🎨 %4zu fragments rendered (%2u ms)\n", i, clock_get()->ms_from_start - ms_curr);
}
