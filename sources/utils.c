/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 20:59:43 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_puterr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int			min(int a, int b)
{
	return ((a > b) ? b : a);
}

t_point		new_point(int x, int y, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}

void		error(char *s)
{
	ft_puterr(s);
	exit(1);
}

t_complex	to_complex(int x, int y, t_fractol *fractol)
{
	return (t_complex){fractol->z_min.x + ((double)x / fractol->picture->width)
			* (fractol->z_max.x - fractol->z_min.x) * fractol->zoom +
			fractol->offset.x, fractol->z_min.y + ((double)y /
			fractol->picture->height) * (fractol->z_max.y -
			fractol->z_min.y) * fractol->zoom + fractol->offset.y};
}
