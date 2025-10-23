/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:37:11 by csuomins          #+#    #+#             */
/*   Updated: 2025/10/23 18:16:00 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init(); // inicializa a conexão como x11 (sistema gráfico)
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Fract-ol");
	if (!data.win_ptr)
		return (1);
	create_image(&data, 800, 600);
	init_mandelbrot(&data);
	
	data.last_render_time = 0;
	data.last_zoom_time = 0;
	data.is_zooming = 0;
	
	render_mandelbrot(&data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_key, &data); // 2 = evento "tecla foi pressionada" 1L << 0 = mascara que ativa o evento de tecla
	mlx_mouse_hook(data.win_ptr, handle_mause, &data);
	mlx_hook(data.win_ptr, 17, 0, handle_close, &data);
	mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
	mlx_loop(data.mlx_ptr); // matém a janela aberta até fecharmos
}
