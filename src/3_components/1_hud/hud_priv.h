#ifndef HUD_PRIV
# define HUD_PRIV

# include "data.h"

# define HUD_LOADING_MS				250

typedef enum e_hud_obj
{
	HUD_OBJ_BACKGROUND,
	HUD_OBJ_LOADING,
	HUD_OBJ_XAV,
	HUD_OBJ_COUNT
}	t_hud_obj;

typedef enum e_component_id
{
	HUD,
	MAP,
	PLAYER,
	COMPONENT_COUNT
}	t_component_id;

typedef struct s_animation
{
	t_object	object;
	bool		(*fn_init)(t_data *data, struct s_animation *self);	// useless if nothing owned ?
	bool		(*fn_load)(t_data *data, struct s_animation *self);
	bool		(*fn_free)(t_data *data, struct s_animation *self);	// useless if nothing owned ?
	
	bool		(*fn_play)(t_data *data, struct s_animation *self);
	bool		(*fn_play_during)(t_data *data, struct s_animation *self, size_t ms);
	bool		(*fn_stop)(t_data *data, struct s_animation *self);
}	t_animation;

typedef struct s_component
{
	t_component_id	component_id;
	bool	(*fn_init)(t_data *data, struct s_component *self);
	bool	(*fn_load)(t_data *data, struct s_component *self);
	bool	(*fn_free)(t_data *data, struct s_component *self);
	
	int		(*handle_frame)(t_data *data, struct s_component *self);
	int		(*handle_event)(int envent, t_data *data, struct s_component *self);
}	t_component;

// background
bool	hud_background_create(t_data *data);

// loading
bool	hud_loading_create(t_data *data);
bool	hud_loading_play(t_data *data, size_t duration_ms);
bool	hud_loading_callback(void *data, struct s_object *object);

// xav
bool	hud_xav_create(t_data *data);
bool	hud_xav_play(t_data *data);

#endif
