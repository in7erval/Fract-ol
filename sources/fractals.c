/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/30 16:27:42 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pixel			unnamed1(int x, int y, t_fractol *fractol)
{
	t_complex zk;
	t_pixel p;
	t_complex z;

	z.x = fractol->z_min.x + ((double)x / fractol->picture->width) *
							 (fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->offset.x;
	z.y = fractol->z_min.y + ((double)y / fractol->picture->height) *
							 (fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->offset.y;
	p.k = 0;
	while (1)
	{
		zk.x = (z.x + z.y) * (z.x - z.y) - fractol->c.x;
		zk.y = 2 * fabs(z.x) * z.y + fractol->c.y;
		if (!((p.r = zk.x * zk.x + zk.y * zk.y) < fractol->r && p.k < fractol->k))
			break;
		if (zk.x == z.x && zk.y == z.y)
		{
			p.k = fractol->k;
			break;
		}
		z = zk;
		p.k++;
	}
	return (p);
}

t_pixel			unnamed2(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_pixel		p;
	t_complex	zk;

	z.x = fractol->z_min.x + ((double)x / fractol->picture->width) *
			(fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->offset.x;
	z.y = fractol->z_min.y + ((double)y / fractol->picture->height) *
			(fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->offset.y;
	p.k = 0;
	while (1)
	{
		zk.x = (z.x + z.y) * (z.x - z.y) - fractol->c.x;
		zk.y = z.x * fabs(z.y) * -2.0 - fractol->c.y;
		if (!((p.r = zk.x * zk.x + zk.y * zk.y) < fractol->r && p.k < fractol->k))
			break ;
		if (z.x == zk.x && z.y == zk.y)
		{
			p.k = fractol->k;
			break ;
		}
		z = zk;
		p.k++;
	}
	return (p);
}

t_pixel	mandelbrot(int x, int y, t_fractol *fractol)
{
	t_complex	zk;
	t_complex	c;
	t_pixel		p;
	t_complex	z;


	z.x = fractol->z_min.x + ((double)x / fractol->picture->width) *
			(fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->offset.x;
	z.y = fractol->z_min.y + ((double)y / fractol->picture->height) *
			(fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->offset.y;
	c = z;
	p.k = 0;
	while ((p.r = z.x * z.x + z.y * z.y) < fractol->r && p.k < fractol->k)
	{
		zk.x = (z.x + z.y) * (z.x - z.y) + c.x;
		zk.y = z.x * z.y * 2 + c.y;
		if (z.x == zk.x && z.y == zk.y)
		{
			p.k = fractol->k;
			break ;
		}
		z = zk;
		p.k++;
	}
	return (p);
}

t_pixel	julia(int x, int y, t_fractol *fractol)
{
	t_complex zk;
	t_pixel p;
	t_complex z;

	z.x = fractol->z_min.x + ((double)x / fractol->picture->width) *
							 (fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->offset.x;
	z.y = fractol->z_min.y + ((double)y / fractol->picture->height) *
							 (fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->offset.y;
	p.k = 0;
	while (1)
	{
		zk.x = (z.x + z.y) * (z.x - z.y) + fractol->c.x;
		zk.y = 2 * z.x * z.y + fractol->c.y;
		if (!((p.r = zk.x * zk.x + zk.y * zk.y) < fractol->r && p.k < fractol->k))
			break;
		if (zk.x == z.x && zk.y == z.y)
		{
			p.k = fractol->k;
			break;
		}
		z = zk;
		p.k++;
	}
	return (p);
}
