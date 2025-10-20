/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:51:51 by csuomins          #+#    #+#             */
/*   Updated: 2025/10/20 17:21:21 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	create_image(t_data *data, int width, int height)
{
	t_img	img;

	data->img.width = width;
	data->img.height = height;
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, width, height);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
}