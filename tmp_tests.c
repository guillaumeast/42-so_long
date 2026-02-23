// #include "data.h"

# include <stdbool.h>
# include <stddef.h>

/* ************************************************************************* */
/*                                  CLOCK                                    */
/* ************************************************************************* */

typedef struct s_clock
{
	size_t	ms;
	size_t	tick;
	size_t	tps;
	size_t	frame;
	size_t	fps;
}	t_clock;


/* ************************************************************************* */
/*                                   OBJECT                                    */
/* ************************************************************************* */

typedef struct s_object
{
	void			*model;
	t_view			view;
	t_controller	controller;
}	t_object;

typedef struct t_render_pipe
{}	t_pipe;
/*------------------------------*/

#define SPRITES_FOLDER				"sprites/"

/*------------------------------*/

/* --- GLOBAL --- */

#define HUD_SPRITES_FOLDER			SPRITES_FOLDER "hud/"				// ==> "sprites/hud/"

typedef enum e_hud_sprites_id
{
	HUD_SPRITES_BG,
	HUD_SPRITES_LOADING,
	HUD_SPRITES_COUNT
}	t_hud_sprites_id;

/* --- BACKGROUND --- */

#define HUD_SPRITES_BG_FOLDER		HUD_SPRITES_FOLDER "background/"	// ==> "sprites/hud/background"
#define HUD_SPRITES_BG_HEIGHT_PX	11
#define HUD_SPRITES_BG_WIDTH_PX		1250

typedef enum e_hud_sprite_bg_id
{
	HUD_SPRITE_BG_1,
	HUD_SPRITE_BG_COUNT
}	t_hud_sprite_bg_id;

t_sprite_set hud_sprites_bg(void)
{
	return (sprite_set_new(
		HUD_SPRITES_BG_FOLDER,
		HUD_SPRITE_BG_COUNT,
		HUD_SPRITES_BG_HEIGHT_PX,
		HUD_SPRITES_BG_WIDTH_PX));
}

/* --- LOADING --- */

#define HUD_SPRITES_LOADING_FOLDER		HUD_SPRITES_FOLDER "loading/"	// ==> "sprites/loading/"
#define HUD_SPRITES_LOADING_HEIGHT_PX	11
#define HUD_SPRITES_LOADING_WIDTH_PX	1250
#define HUD_SPRITES_LOADING_COUNT		10

t_sprite_set hud_sprites_load(void)
{
	return (sprite_set_new(
		HUD_SPRITES_BG_FOLDER,
		HUD_SPRITE_LOADING_COUNT,
		HUD_SPRITES_LOADING_HEIGHT_PX,
		HUD_SPRITES_LOADING_WIDTH_PX));
}

/* --- USAGE --- */

typedef enum e_hud_obj_id
{
	HUD_BG,
	HUD_LOAD,
	HUD_OBJ_COUNT
}	t_hud_obj_id;

typedef enum e_hud_anim_id
{
	HUD_ANIM_LOAD_FORWARD,
	HUD_ANIM_LOAD_BACKWARD,
	HUD_ANIM_LOAD_FULL,
	HUD_ANIM_COUNT
}	t_hud_anim_id;

void	sprites_init(t_sprite_set *sprite_set);
bool	sprites_load(t_sprite_set *sprite_set);
bool	sprites_free(t_sprite_set *sprite_set);

void	animation_init(t_animation *animation);
bool	animation_load(t_animation *animation);
bool	animation_free(t_animation *animation);

void	object_init(t_object *object);
bool	object_load(t_object *object);
bool	object_free(t_object *object);

void	controller_init(t_controller *controller);					// Propaged to children
bool	controller_load(t_controller *controller, t_data *data);	// Propaged to children
bool	controller_free(t_controller *controller);					// Propaged to children

typedef struct s_hud_data
{
	// ...
	t_sprite_set	sprite_sets[HUD_SPRITES_COUNT];	// Raw bundles of images
	t_animation		animation[HUD_ANIM_COUNT];		// polished bundles wich can use several sprite_sets
	t_object		objects[HUD_OBJ_COUNT];			// objects which can use several animations
	// ...
}	t_hud_data;

bool		hud_load_sprites(t_hud_data *data)
{
	// ...
	data->sprite_sets[HUD_SPRITES_BG] = hud_sprites_bg();
	data->sprite_sets[HUD_SPRITES_LOADING] = hud_sprites_load();
	// ...
}

bool		hud_load_objects(t_hud_data *data)
{
	// ...
	data->objects[HUD_BG] = hud_object_bg();
	data->objects[HUD_LOAD] = hud_object_load();
	// ...
}

t_object	hud_object_bg(t_hud_data *data)
{
	return (object_new(
		position_new_static(0, 1),
		texture_new_static(data->sprite_sets[HUD_SPRITES_BG], HUD_SPRITE_BG_1),
		NULL
	));
}

/*------------------------------*/

# define HUD_POSITION_START_Y	400
# define HUD_POSITION_START_X	750

// object_1_load()		=> appelle la fonction couteuse sprite_set_new (qui charge les images en mémoire)
// object_1_create()	=> applle la fonction cheap

bool	hud_object_1_load(t_object *object)
{
	t_sprite_set	sprite_set;

	sprite_set = sprite_set_new(
		HUD_SPRITES_PATH,
		HUD_SPRITES_HEIGHT_PX,
		HUD_SPRITES_WIDTH_PX,
		HUD_SPRITES_COUNT);
	*object = object_new_static(
		HUD_POSITION_START_Y,
		HUD_POSITION_START_X,
		sprite_set.images[2],	// Le module texture doit contenir sprite_set et garder un tableau statique de tous les sprite_set pour y accéder seul et fast
		hud_object_callback);		// opt:Le callback est toujours sur last_frame, sinon utiliser handle_frame
	return (true);
}

// Chacun component doit être call (via les controllers) pour que chaque objet puisse load ses sprites
// Ensuite seulement les objets peuvent être créés, permettant d'éviter un if et d'accéder aux images le plus rapidement possible


// -1 = init
t_object	hud_animation_1(int ms)
{
	static t_object background;
	static t_object animation;

	if (ms == -1)
	{
		background = 
	}
	background = object_new()
}

bool	hud_object_callback(t_data *data, t_object *object)
{
	return ;
}