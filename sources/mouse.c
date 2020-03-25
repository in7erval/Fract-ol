/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/30 16:26:26 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		zoom(int x, int y, t_fractol *fractol, double zoom)
{
	double w;
	double h;
	double nw;
	double nh;

	w = (fractol->z_max.x - fractol->z_min.x) * fractol->zoom;
	h = (fractol->z_max.y - fractol->z_min.y) * fractol->zoom;
	nw = (fractol->z_max.x - fractol->z_min.x) * (fractol->zoom * zoom);
	nh = (fractol->z_max.y - fractol->z_min.y) * (fractol->zoom * zoom);
	fractol->zoom *= zoom;
	fractol->offset.x -= ((double)x / fractol->picture->width) * (nw - w);
	fractol->offset.y -= ((double)y / fractol->picture->height) * (nh - h);
}

int			mouse_press(int button, int x, int y, t_fractol *fractol)
{
	if (button == MOUSE_SCROLL_UP)
		zoom(x, y, fractol, ZOOM);
	if (button == MOUSE_SCROLL_DOWN)
		zoom(x, y, fractol, 1 / ZOOM);
	if (button == MOUSE_RIGHT_CLICK)
		fractol->mouse_status = PRESSED_RIGHT;
	if (button == MOUSE_LEFT_CLICK)
		fractol->mouse_status = PRESSED_LEFT;
	draw(fractol);
	return (0);
}

int			mouse_release(int button, int x, int y, t_fractol *fractol)
{
	(void)x;
	(void)y;
	(void)button;
	fractol->mouse_status = NOTPRESSED;
	return (0);
}

int			mouse_move(int x, int y, t_fractol *fractol)
{

	fractol->mouse_prevpos = fractol->mouse_pos;
	fractol->mouse_pos = (t_complex){.x = x, .y = y};
	if (fractol->fract != MANDELBROT)
	{
		fractol->c.x = ((double) x / fractol->picture->width) * (fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->z_min.x + fractol->offset.x;
		fractol->c.y = ((double) y / fractol->picture->height) * (fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->z_min.y + fractol->offset.y;
	}
	if (fractol->mouse_status == PRESSED_LEFT)
	{
		fractol->offset.x += (double)(fractol->mouse_prevpos.x - fractol->mouse_pos.x) / fractol->picture->width * (fractol->z_max.x - fractol->z_min.x) * fractol->zoom;
		fractol->offset.y += (double)(fractol->mouse_prevpos.y - fractol->mouse_pos.y) / fractol->picture->height * (fractol->z_max.y - fractol->z_min.y) * fractol->zoom;
	}
	draw(fractol);
	return (0);
}
