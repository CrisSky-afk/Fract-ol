#include "fractol.h"

void    create_image(t_data *data, int width, int height)
{
    data->img.width = width;
    data->img.height = height;
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, width, height);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
             &data->img.line_len, &data->img.endian);
}
void    init_mandelbrot(t_data *data)
{
    double  aspect_ratio;

    aspect_ratio = (double)data->img.width / data->img.height;
    data->img.max_i = 2.0;
    data->img.min_i = -2.0;
    data->img.max_r = 2.0 * aspect_ratio;
    data->img.min_r = -2.0 * aspect_ratio;
    data->img.iteração_maxima = 500;
}
void	img_pix_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)(img->addr + offset) = color;
}
