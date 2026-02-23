#ifndef OBJECT_H
# define OBJECT_H

# include "position.h"
# include "texture.h"

# define OBJECT_BACKGROUND_CAP	4

typedef enum e_object_type
{
	OBJECT_HUD_BACKGROUND,
	OBJECT_HUD_LOADING,
	// OBJECT_HUD_EYE,
	// OBJECT_HUD_SCREEN,
	// OBJECT_MAP,
	// OBJECT_PLAYER,
	OBJECT_COUNT
}	t_object_type;

typedef enum e_object_status
{
	OBJ_STATUS_HIDDEN,
	OBJ_STATUS_QUEUED,
	OBJ_STATUS_RENDERING,
	OBJ_STATUS_RENDERED,
	OBJ_STATUS_COUNT
}	t_object_status;

typedef enum e_callback_mode
{
	CALLBACK_NONE,
	CALLBACK_EACH_FRAME,
	CALLBACK_LAST_FRAME
}	t_callback_mode;

typedef struct s_object
{
	t_object_status	status;
	t_position		position;
	t_texture		texture;
	struct s_object	*backgrounds[OBJECT_BACKGROUND_CAP];	// borrowed
	size_t			background_count;
	t_callback_mode	callback_mode;
	bool			(*fn_callback)(void *param, struct s_object *object);
}	t_object;

typedef struct s_callback
{
	bool			(*fn_callback)(void *param, struct s_object *object);
	t_callback_mode	mode;
}	t_callback;

// Backgrounds must be set manually
t_callback	callback_new(
	bool			(*fn_callback)(void *param, struct s_object *object),
	t_callback_mode	mode);
bool	object_add_callback(
	void 			*param,
	t_object		*object,
	bool			(*fn_callback)(void *param, struct s_object *object),
	t_callback_mode	mode);
t_object	object_new(
	t_position		position,
	t_texture		texture,
	bool			(*fn_callback)(void *param, struct s_object *object),
	t_callback_mode	mode);
t_object	object_new_static(int x, int y, t_sprite_set_id set_id, size_t image_id);
void		object_print(t_object *object);

#endif
