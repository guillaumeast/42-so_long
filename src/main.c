#include "mlx.h"
#include "apple.h"
#include "libft.h"
#include "view.h"

# include "logs.h"

int	main(void)
{
	void	*mlx_ptr;
	t_view	view;

	print_start(99, "main()");
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (print_err(true, "Mlx init failed"), 1);
	view_init(&view);
	if (!view_load(mlx_ptr, &view))
	{
		view_free(mlx_ptr, &view);
		mlx_destroy_display(mlx_ptr);
		return (1);
	}
	if (!view_launch(mlx_ptr, &view))
	{
		view_free(mlx_ptr, &view);
		mlx_destroy_display(mlx_ptr);
		return (1);
	}
	view_free(mlx_ptr, &view);
	mlx_destroy_display(mlx_ptr);
	return (0);
}
