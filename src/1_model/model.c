#include "model.h"
#include <stdlib.h>

# include "logs.h"

void	model_init(void)
{
	print_pass("Model initialized\n");
}

bool	model_load(void)
{
	print_pass("Model loaded\n");
	return (true);
}

void	model_free(void)
{
	print_info("Model free'd\n");
	model_init();
}
