/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:39:52 by csuomins          #+#    #+#             */
/*   Updated: 2025/10/23 17:30:35 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_math(t_data *data, double x, double y)
{
	int		itera;
	int		iter;
	double	temp;

	itera = 0;
	iter = (int)(ITER_BASE * data->img.iter_mult);
	data->img.coord_complexa_i = data->img.min_i
		+ (y * (data->img.max_i - data->img.min_i)) / data->img.height;
	data->img.coord_complexa_r = data->img.min_r
		+ (x * (data->img.max_r - data->img.min_r)) / data->img.width;

	data->img.z_i = 0;
	data->img.z_r = 0;
	while (itera < iter)
	{
		temp = (data->img.z_r * data->img.z_r)
			- (data->img.z_i * data->img.z_i) + data->img.coord_complexa_r;
		data->img.z_i = 2 * (data->img.z_i * data->img.z_r)
			+ data->img.coord_complexa_i;
		data->img.z_r = temp;
		if ((data->img.z_r * data->img.z_r)
			+ (data->img.z_i * data->img.z_i) > 4)
			break ;
		itera++;
	}
	if (itera == iter)
		return (0x121e0f);
	else
		return (0x729e64);
}

void	render_mandelbrot(t_data *data)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x < data->img.width)
		{
			color = mandelbrot_math(data, x, y);
			img_pix_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, 0, 0);
}
