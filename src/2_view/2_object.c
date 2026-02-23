#include "view.h"
#include "view_render.h"

void	object_new(t_object *object, int pos_y, int pos_x, t_skin skin)
{
	*object = (t_object){ 0 };
	object->skin = skin;
	element_new(&object->element_3D, pos_y, pos_x, skin.sprites.images[0]);
}

void	object_move_by(t_object *object, int total_y, int total_x, uint ms)
{
	element_set_movement(&object->element_3D, total_y, total_x, ms);
}

void	object_move_to(t_object *object, int dst_y, int dst_x, uint ms)
{
	element_set_movement(
		&object->element_3D,
		dst_y - object->element_3D.element_2D.fragment.y,
		dst_x - object->element_3D.element_2D.fragment.x,
		ms);
}

void	object_apply_skin(t_object *object, t_skin skin)
{
	element_set_animation(
		&object->element_3D,
		skin.sprites.images,
		skin.sprites.count,
		skin.ms_anim);
	object->skin = skin;
}

void	object_apply_skin_ms(t_object *object, t_skin skin, uint ms)
{
	element_set_animation(
		&object->element_3D,
		skin.sprites.images,
		skin.sprites.count,
		ms);
	object->skin = skin;
}

void	object_set_callbacks(t_object *object, t_fn_callback on_frame, t_fn_callback on_last)
{
	element_set_callback(&object->element_3D, on_frame, on_last, object->data);
}

void	object_add_background(t_object *dst, t_object *background)
{
	element_add_background(&dst->element_3D, background->element_3D.element_2D);
}

bool	object_render(t_object *object)
{
	return (render_element(&object->element_3D));
}

void	object_cancel_render(t_object *object)
{
	render_cancel_element(&object->element_3D);
}
