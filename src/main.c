#include "mlx.h"
#include "data.h"

# include "logs.h"

int	main(void)
{
	t_data	data;

	print_start(99, "main()");
	data = data_init();
	if (!data_load(&data))
		return (data_free(&data), 1);
	print_warn("launching loop\n");
	mlx_loop(data.mlx_ptr);
	data_free(&data);
	return (0);
}
