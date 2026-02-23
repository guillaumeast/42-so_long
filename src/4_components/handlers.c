#include "hud.h"
#include "controller.h"

# include "logs.h"

void	my_controller_init(t_controller *self)
{
	(void)self;
	print_info("HUD initialized\n");
}

bool	my_controller_load(t_controller *self)
{
	hud_load_skins(self->data);
	print_info("HUD loaded\n");
	return (true);
}

void	my_controller_free(t_controller *self)
{
	t_hud_data	*data;

	data = self->data;
	skin_free_all(data->skins, SKIN_HUD_COUNT);
	print_info("HUD free'd\n");
}

int	my_controller_event(t_controller *self, int event)
{
	(void)self;
	(void)event;
	print_info("HUD event handled\n");
	return (0);
}

int	my_controller_frame(t_controller *self, t_clock clock)
{
	(void)self;
	(void)clock;
	print_info("HUD frame handled\n");
	return (0);
}
