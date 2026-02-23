#include "view_mlx.h"
#include "view_settings.h"
#include "view_render.h"

void	view_init(void)
{
	return ;
}

bool	view_load(void)
{
	return (view_mlx_load(WINDOW_HEIGHT_PX, WINDOW_WIDTH_PX, WINDOW_TITLE));
}

void	view_flush(void)
{
	render_flush();
}

void	view_free(void)
{
	view_mlx_free();
}
