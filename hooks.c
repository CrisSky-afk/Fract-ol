#include "fractol.h"

int     handle_close(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}

int     handle_key(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
    {
        handle_close(data);
    }
    return (0);
}
