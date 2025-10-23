/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:39:31 by csuomins          #+#    #+#             */
/*   Updated: 2025/10/23 18:10:41 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <sys/time.h>
# include "mlx.h"
# define KEY_ESC 65307
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_LEFT 97
# define KEY_RIGHT 100
# define MOVE_STEP 0.1
# define ZOOM_IN 0.9
# define ZOOM_OUT 1.1
# define ITER_BASE 500
# define RENDER_DELAY_MS 50
# define ZOOM_DEBOUNCE_MS 200

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	double	max_r;
	double	min_r;
	double	max_i;
	double	min_i;
	double	z_r;
	double	z_i;
	double	coord_complexa_r;
	double	coord_complexa_i;
	double	iter_mult;
}	t_img;

typedef struct s_data {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	long long	last_render_time;
	long long	last_zoom_time;
	int			is_zooming;
}	t_data;

void	create_image(t_data *data, int width, int height);
void	img_pix_put(t_img *img, int x, int y, int color);
void	init_mandelbrot(t_data *data);
int		mandelbrot_math(t_data *data, double x, double y);
void	render_mandelbrot(t_data *data);
int		handle_close(t_data *data);
int		handle_key(int keycode, t_data *data);
void	move_fractal(t_data *data, double dx, double dy);
void	zoom_center(t_data *data, double factor);
int		handle_mause(int button, int x, int y, t_data *data);
int		loop_hook(t_data *data);
long long	get_time_ms(void);

#endif
