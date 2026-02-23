#include "controller_priv.h"

# include "logs.h"

void	controller_init(void)
{
	propagate_init(controller_get());
	print_pass("Controllers initialized\n");
}

bool	controller_load(void)
{
	bool	res;

	res = propagate_load(controller_get());
	if (res)
		print_pass("Controllers loaded\n");
	else
		print_error("Some controller load has fail\n");
	return (res);
}

void	controller_free(void)
{
	propagate_free(controller_get());
	print_pass("Controllers free'd\n");
}
