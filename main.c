#include "fractol.h"

int main (void)
{
    t_data  data;

    data.mlx_ptr = mlx_init(); // inicializa a conexão como x11 (sistema gráfico)
    if (!data.mlx_ptr)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 1200, 900, "Fract-ol");
    if (!data.win_ptr)
        return (1);
    create_image(&data, 1200, 900);
    init_mandelbrot(&data);
    render_mandelbrot(&data);
    mlx_hook(data.win_ptr, 2, 1L << 0, handle_key, &data); // 2 = evento "tecla foi pressionada" 1L << 0 = mascara que ativa o evento de tecla
    mlx_hook(data.win_ptr, 17, 0, handle_close, &data);
    mlx_loop(data.mlx_ptr); // matém a janela aberta até fecharmos
}
