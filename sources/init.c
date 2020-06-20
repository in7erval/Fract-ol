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

t_picture		*picture_init(char *name, int width, int height)
{
	t_picture	*picture;

	if (!(picture = (t_picture *)malloc(sizeof(t_picture))))
		return (NULL);
	picture->width = width;
	picture->height = height;
	picture->mlx = mlx_init();
	picture->win = mlx_new_window(picture->mlx, width, height, name);
	picture->img = mlx_new_image(picture->mlx, width, height);
	picture->data_addr = mlx_get_data_addr(picture->img,
			&(picture->bits_per_pixel), &(picture->size_line),
			&(picture->endian));
	picture->bits_per_pixel /= 8;
	ft_bzero(picture->data_addr, width * height *
	(picture->bits_per_pixel / 8));
	return (picture);
}

static void		init_z(t_fractol *f)
{
	f->z_max = (t_complex){.x = 2.0, .y = 2.0};
	f->z_min = (t_complex){.x = -2.0, .y = -2.0};
}

t_fractol		*fractol_init(t_picture *picture, int name)
{
	t_fractol	*fractol;

	if (!(fractol = (t_fractol *)malloc(sizeof(t_fractol))))
		return (NULL);
	fractol->pixel_data = (t_pixel *)malloc(sizeof(t_pixel)
	* picture->height * picture->width);
	fractol->picture = picture;
	init_z(fractol);
	fractol->c.x = 0;
	fractol->c.y = 0;
	fractol->mouse_status = NOTPRESSED;
	fractol->mouse_pos.x = picture->width / 2;
	fractol->mouse_pos.y = picture->height / 2;
	fractol->color = 0;
	fractol->fract = name;
	fractol->zoom = 1;
	fractol->offset = (t_complex){.x = 0, .y = 0};
	fractol->cycle = 0;
	fractol->r = 4;
	fractol->k = 32;
	return (fractol);
}
