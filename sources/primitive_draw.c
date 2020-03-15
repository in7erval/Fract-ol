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

void			put_pixel(t_picture *picture, t_point p)
{
	if (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
		*(int *)(picture->data_addr + (p.x + p.y * WIDTH) * picture->bits_per_pixel) = p.color;
}

static void		action(t_point *p, int sign[3], int v[2], int *f)
{
	*f += (sign[0] == 1) ? v[1] * sign[2] : v[0] * sign[1];
	if (*f > 0)
	{
		*f -= (sign[0] == 1) ? v[0] * sign[1] : v[1] * sign[2];
		if (sign[0] == 1)
			p->x -= sign[2];
		else
			p->y += sign[1];
	}
	if (sign[0] == 1)
		p->y += sign[1];
	else
		p->x -= sign[2];
}

void			put_line(t_picture *picture, t_point p0, t_point p1)
{
	int		v[2];
	int		sign[3];
	int		f;
	float	length;
	t_point p;

	v[0] = p1.y - p0.y;
	v[1] = p0.x - p1.x;
	sign[0] = (abs(v[0]) > abs(v[1])) ? 1 : -1;
	sign[1] = (v[0] < 0) ? -1 : 1;
	sign[2] = (v[1] < 0) ? -1 : 1;
	f = 0;
	put_pixel(picture, p0);
	p = p0;
	length = sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2));
	while (p.x != p1.x || p.y != p1.y)
	{
		action(&p, sign, v, &f);
		p.color = get_color(p0.color, p1.color, sqrt(pow((p.x - p0.x), 2) + pow((p.y - p0.y), 2)) / length);
		put_pixel(picture, p);
	}
}

