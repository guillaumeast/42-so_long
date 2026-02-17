#ifndef APPLE_H
# define APPLE_H

# ifdef __APPLE__
int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
int mlx_loop_end (void *mlx_ptr);
int	mlx_destroy_display(void *mlx_ptr);
# endif

#endif
