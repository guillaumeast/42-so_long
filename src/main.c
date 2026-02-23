#include "model.h"
#include "view.h"
#include "controller.h"

# include "logs.h"

static inline void	main_free(void);

int	main(void)
{
	print_start(99, "main()");
	clock_init();
	print_pass("clock initialized ");
	clock_print();
	// Load game related data (parse map, set game default values...)
	model_load();
	// Load graphic module (needed by controllers to load assets / register to the render pipe)
	view_load();
	// Load assets (parse and load sprites, build animations and 3D objects, set handlers...)
	controller_load();
	// Set handlers (event, tick, win close...)
	controller_set_handlers();
	// Start game loop
	controller_play();
	// Stop game loop
	controller_stop();
	// Free all
	main_free();
	print_result("Congrats!");
	return (0);
}

static inline void	main_free(void)
{
	controller_free();
	view_free();
	model_free();
}
