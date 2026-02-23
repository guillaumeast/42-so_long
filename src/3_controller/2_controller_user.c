#include "controller.h"
#include "mlx.h"
#include "view_mlx.h"

# include "logs.h"

t_controller	*controller_get(void)
{
	static t_controller controller = { 0 };

	return (&controller);
}

void	controller_play(void)
{
	print_warn("Launching loop 🕹️\n");
	mlx_loop(view_mlx_get()->mlx_ptr);
}

void	controller_stop(void)
{
	print_warn("Stopping loop 🕹️\n");
	mlx_loop_end(view_mlx_get()->mlx_ptr);
}
