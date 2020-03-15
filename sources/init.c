/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/30 13:22:57 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_picture	*picture_init(void)
{
	t_picture	*picture;

	picture = (t_picture *)malloc(sizeof(t_picture));
	picture->mlx = mlx_init();
	picture->win = mlx_new_window(picture->mlx, WIDTH, HEIGHT, "FRACTOL");
	picture->img = mlx_new_image(picture->mlx, WIDTH, HEIGHT);
	picture->data_addr = mlx_get_data_addr(picture->img, &(picture->bits_per_pixel),
										   &(picture->size_line), &(picture->endian));
	ft_bzero(picture->data_addr, WIDTH * HEIGHT * (picture->bits_per_pixel / 8));
	return (picture);
}

void		init_z(t_fractol *f, int name)
{
	if (name == MANDELBROT)
	{

		f->z_max = (t_complex){.x = 2.0, .y = 2.0};
		f->z_min = (t_complex){.x = -2.0, .y = -2.0};
	}
	if (name == JULIA)
	{
		f->z_max = (t_complex){.x = 2.0, .y = 2.0};
		f->z_min = (t_complex){.x = -2.0, .y = -2.0};
	}
}

t_fractol	*fractol_init(t_picture *picture, int name)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)malloc(sizeof(t_fractol));
	fractol->pixel_data = (t_pixel *)malloc(sizeof(t_pixel) * HEIGHT * WIDTH);
	fractol->picture = picture;
	init_z(fractol, name);
	fractol->c.x = 0;
	fractol->c.y = 0;
	fractol->mouse_status = NOTPRESSED;
	fractol->mouse_pos.x = WIDTH / 2;
	fractol->mouse_pos.y = HEIGHT / 2;
	fractol->color = 0;
	fractol->fract = name;
	fractol->zoom = 1;
	fractol->offset = (t_complex){.x = 0, .y = 0};
	fractol->cycle = 0;
	return (fractol);
}
