#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include "mlx.h"
# define KEY_ESC 65307

typedef struct s_img {
    void    *img_ptr;   // ponteiro para a imagem na memória (criada pelo mlx_new_image)
    char    *addr;      // endereço de memória onde os pixels ficam
    int     bpp;        // bites por pixel (geralmente 32)
    int     line_len;   // quantos bytes cada linha da imagem ocupa na memoria
    int     endian;     // ordem dos bytes (0 = little endian, 1 = big endian)
    int     width;      // largura da imagem em pixels
    int     height;     // altuura da imagem em pixels
    double  max_r;
    double  min_r;
    double  max_i;
    double  min_i;
    double  z_r;
    double  z_i;
    int     iteração_maxima;
    double  coord_complexa_r;
    double  coord_complexa_i;
} t_img;

typedef struct s_data {
    void    *mlx_ptr;   // ponteiro para MLX (x11) (inicialização)
    void    *win_ptr;   // ponteiro da janela 
    t_img   img;        // imagem onde vamos desenhar
} t_data;

void    create_image(t_data *data, int width, int height);
void	img_pix_put(t_img *img, int x, int y, int color);
void    init_mandelbrot(t_data *data);
int    mandelbrot_math(t_data *data, double x, double y);
void    render_mandelbrot(t_data *data);
int     handle_close(t_data *data);
int     handle_key(int keycode, t_data *data);

#endif
