#include "libft.h"
#include "mlx.h"
#include "apple.h"
#include "data.h"

# include "logs.h"

t_data	data_init(void)
{
	return ((t_data)
		{
			.mlx_ptr = NULL,
			.model = model_init(),
			.view = view_init(),
			.control = control_init()
		});
}

bool	data_load(t_data *data)
{
	print_title("data_load()");
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (print_err(true, "Mlx init failed"), false);
	print_pass("mlx loaded\n");
	if (!model_load(&data->model))
		return (false);
	print_pass("model loaded\n");
	if (!view_load(data->mlx_ptr, &data->view))
		return (false);
	print_pass("view loaded\n");
	if (!control_load(&data->control, data))
		return (false);
	print_pass("control loaded\n");
	print_result("data loaded");
	return (true);
}

void	data_free(t_data *data)
{
	model_free(&data->model);
	control_free(&data->control);
	view_free(data->mlx_ptr, &data->view);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	*data = data_init();
}
