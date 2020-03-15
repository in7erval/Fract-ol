/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/30 16:14:33 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# define NUM_PROC	10
# define KEY_ESC 	53
# define KEY_1_UP 	18
# define KEY_2_UP 	19
# define KEY_3_UP 	20
# define KEY_4_UP 	21
# define KEY_5_UP 	23
# define KEY_6_UP 	22
# define KEY_7_UP 	26
# define KEY_8_UP 	28
# define KEY_9_UP	25
# define KEY_0_UP 	29
# define KEY_1_PAD 	83
# define KEY_2_PAD 	84
# define KEY_3_PAD 	85
# define KEY_4_PAD 	86
# define KEY_5_PAD 	87
# define KEY_6_PAD 	88
# define KEY_7_PAD 	89
# define KEY_8_PAD 	91
# define KEY_9_PAD 	92
# define KEY_0_PAD 	82
# define KEY_SPACE 	49
# define KEY_RIGHT 	124
# define KEY_LEFT  	123
# define KEY_UP    	126
# define KEY_DOWN  	125
# define KEY_MINUS 	27
# define KEY_PLUS  	24
# define KEY_I 		34
# define KEY_P 		35
# define KEY_T 		17
# define KEY_M 		46
# define KEY_MORE 	47
# define KEY_LESS 	43
# define KEY_R 		15
# define KEY_D 		2
# define KEY_F 		3
# define KEY_E 		14
# define KEY_W 		13
# define KEY_B 		11
# define KEY_G 		5
# define KEY_C		8
# define KEY_S		1

# define WIDTH 				1000
# define HEIGHT				1000
# define HEIGHT_OF_HEADER 	30
# define MENU_WIDTH			400
# define MENU_HEIGHT 		420

# define BACKGROUND 		0x222222
# define MENU_BACKGROUND	0x222222
# define HEADER_COLOR 	0x808080
# define MENU_CLR 		0xbbbbbb
# define DEF_CLR 		0x0099EE

# define RED			0xff0000
# define ORANGE		0xff4f00
# define YELLOW		0xf7ff00
# define GREEN 		0x0bda51
# define LIGHT_BLUE	0x1e90ff
# define BLUE       	0x0099EE
# define VIOLET     	0x4d0092

# define DARK_VIOLET        0x1f1b24
# define BACKGROUND_SURFACE 0x121212
# define PRIMARY_VIOLET     0xbb86fc
# define DARK_BLUE          0x3700b3
# define DARK_TURQUOISE     0x03dac5

# define A_BLUE   0x00008b
# define B_BLUE   0x110573
# define C_BLUE   0x16085b
# define D_BLUE   0x170a45
# define E_BLUE   0x16082f
# define F_BLUE   0x10041c
# define BLACK    0x000000
# define A_VIOLET 0x8b00ff
# define B_VIOLET 0xa648ff
# define C_VIOLET 0xbd71ff
# define D_VIOLET 0xd195ff
# define E_VIOLET 0xe2b9ff
# define F_VIOLET 0xf1dcff
# define WHITE    0xffffff

# define ISO      0
# define PARALLEL 1

# define NOTPRESSED    0
# define PRESSED_LEFT  1
# define PRESSED_RIGHT 2

# define MOUSE_LEFT_CLICK  1
# define MOUSE_RIGHT_CLICK 2
# define MOUSE_MID_CLICK   3
# define MOUSE_SCROLL_DOWN 4
# define MOUSE_SCROLL_UP   5

# define MAX_INT  2147483647
# define MIN_INT -2147483648

# define COLOR1 0
# define COLOR2 1

# define JULIA 			1
# define MANDELBROT 	2

# define K	200
# define R	4

# define ZOOM 1.1

typedef	struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_complex
{
	double			x;
	double			y;
}					t_complex;

typedef	struct		s_pixel
{
	double			r;
	int 			k;
}					t_pixel;

typedef	struct		s_picture
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;

}					t_picture;

typedef struct		s_fractol
{
	int				mouse_status;
	t_picture		*picture;
	t_complex		z_max;
	t_complex		z_min;
	t_complex		c;
	t_complex		mouse_pos;
	t_complex		mouse_prevpos;
	t_pixel			*pixel_data;
	int 			color;
	int 			fract;
	double			zoom;
	t_complex		offset;
	int				cycle;
}					t_fractol;

typedef struct		s_palette
{
	uint8_t		count;
	int			cycle;
	int			colors[16];
}					t_palette;

typedef struct		s_thread
{
	t_fractol		*fractol;
	int 			thread_id;
}					t_thread;

void				ft_puterr(char *str);
int					min(int a, int b);
t_fractol			*fractol_init(t_picture *picture, int name);
void				draw_map(t_fractol *fractol);
t_point				new_point(int x, int y, int color);
void				put_pixel(t_picture *picture, t_point p);
void				put_line(t_picture *picture, t_point p0, t_point p1);
int					get_light(int start, int end, double percentage);
int					get_color(int color1, int color2, float percent);
int					deal_key(int keycode, t_fractol *fractol);
int					exit_program(void *param);
int					mouse_press(int button, int x, int y, t_fractol *fdf);
int					mouse_release(int button, int x, int y, t_fractol *fdf);
int					mouse_move(int x, int y, t_fractol *fdf);
void				mlx_hooks(t_fractol *fractol);
void				show_program(t_fractol *fractol);
void				show_menu(t_fractol *fractol);
void				put_rectangles(t_fractol *fractol);
int					ft_isnumber(char *str, int base);
void				error(char *s);
void				rotation(int keycode, t_fractol *fractol);
void				change_proj(int keycode, t_fractol *fractol);
void				zoom_and_move(int keycode, t_fractol *fractol);
void				deal_color(int keycode, t_fractol *fractol);
int					darkmode_color(double percent);
int					rainbow_color(double percent);
int					default_color(double percent);
int					test_color(double percent);
t_picture			*picture_init(void);
t_pixel				mandelbrot(int x, int y, t_fractol *fractol);
t_pixel				julia(int x, int y, t_fractol *fractol);
void				zoom(int x, int y, t_fractol *fractol, double zoom);
#endif
