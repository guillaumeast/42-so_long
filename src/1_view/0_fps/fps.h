#ifndef FPS_H
# define FPS_H

# include <stdbool.h>
# include <stddef.h>

# define FPS			60
# define FPS_AVG_SIZE	10

size_t	fps_ms_to_frames(size_t ms);
size_t	fps_frames_to_ms(size_t frames);
bool	fps_should_render(void);
size_t	fps_time_in_ms(void);

# endif
