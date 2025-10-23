/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:39:15 by csuomins          #+#    #+#             */
/*   Updated: 2025/10/23 18:19:30 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long long	get_time_ms(void)
{
	struct	timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int	handle_close(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

void	move_fractal(t_data *data, double dx, double dy)
{
	double	range_r;
	double	range_i;

	range_r = data->img.max_r - data->img.min_r;
	range_i = data->img.max_i - data->img.min_i;

	data->img.min_r += dx * range_r;
	data->img.max_r += dx * range_r;
	data->img.min_i += dy * range_i;
	data->img.max_i += dy * range_i;

	data->is_zooming = 1;
	data->last_zoom_time = get_time_ms();
	data->img.iter_mult = 0.1;
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		handle_close(data);
	}
	else if (keycode == KEY_UP)
		move_fractal(data, 0, -MOVE_STEP);
	else if (keycode == KEY_DOWN)
		move_fractal(data, 0, MOVE_STEP);
	else if (keycode == KEY_LEFT)
		move_fractal(data, -MOVE_STEP, 0);
	else if (keycode == KEY_RIGHT)
		move_fractal(data, MOVE_STEP, 0);
	return (0);
}

void	zoom_center(t_data *data, double factor)
{
	double	tamanho_r;
	double	tamanho_i;
	double	center_r;
	double	center_i;
	double	novo_tamanho_r;
	double	novo_tamanho_i;

	tamanho_r = data->img.max_r - data->img.min_r;
	tamanho_i = data->img.max_i - data->img.min_i;
	
	center_r = (data->img.max_r + data->img.min_r) / 2.0;
	center_i = (data->img.max_i + data->img.min_i) / 2.0;

	novo_tamanho_r = tamanho_r * factor;
	novo_tamanho_i = tamanho_i * factor;
	
	data->img.min_r = center_r - novo_tamanho_r / 2.0;
	data->img.max_r = center_r + novo_tamanho_r / 2.0;
	data->img.min_i = center_i - novo_tamanho_i / 2.0;
	data->img.max_i = center_i + novo_tamanho_i / 2.0;

	data->is_zooming = 1;
	data->last_zoom_time = get_time_ms();
	data->img.iter_mult = 0.1;
}

int		handle_mause(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;

	if (button == 4)
		zoom_center(data, ZOOM_IN);
	else if (button == 5)
		zoom_center(data, ZOOM_OUT);
	return (0);
}

int		loop_hook(t_data *data)
{
	long long	current_time;
	long long time_since_zoom;
    long long time_since_render;
	
	if (data->img.iter_mult >= 1.0)
		return (0);
	current_time = get_time_ms();
	time_since_zoom = current_time - data->last_zoom_time;
	
	if (data->is_zooming && time_since_zoom < ZOOM_DEBOUNCE_MS)
        return (0);
	
	if (data->is_zooming && time_since_zoom >= ZOOM_DEBOUNCE_MS)
    {
        data->is_zooming = 0;
        data->last_render_time = 0;
    }
    
    if (data->img.iter_mult >= 1.0)
        return (0);
    
    time_since_render = current_time - data->last_render_time;
    if (time_since_render < RENDER_DELAY_MS)
        return (0);
    
    data->img.iter_mult *= 1.1;
    if (data->img.iter_mult > 1.0)
        data->img.iter_mult = 1.0;
    
    render_mandelbrot(data);
    data->last_render_time = current_time;
    
    return (0);
}
