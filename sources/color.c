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

int		get_light(int start, int end, double percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

int		get_color(int color1, int color2, float percent)
{
	int r;
	int g;
	int b;

	r = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, percent);
	g = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, percent);
	b = get_light(color1 & 0xFF, color2 & 0xFF, percent);
	return ((r << 16) + (g << 8) + b);
}

int			linear_color(int i, t_palette *p)
{
	double		index;
	double		adjust;
	int			c;

	index = (p->cycle) ? fmod((double)i, p->cycle - 1) / (p->cycle - 1) : (double)i / 32;
	c = p->count - 1;
	adjust = fmod(index, (1.0f / c)) * c;
	return (get_color((p->colors[(int)(index * c) + 1]), (p->colors[(int)(index * c)]), (int)(adjust + 1) - adjust));
}

int			get_linear_color(t_pixel p, t_fractol *fractol)
{
	static t_palette pal[6];

	pal[0] = (t_palette){5, 0, {0x002F2F, 0x046380, 0xEFECCA, 0xA7A37E, 0xE6E2AF}};
	pal[1] = (t_palette){5, 0, {BACKGROUND_SURFACE, DARK_TURQUOISE, DARK_BLUE, DARK_VIOLET, PRIMARY_VIOLET}};
	pal[2] = (t_palette){5, 0, {BACKGROUND_SURFACE, DARK_VIOLET, DARK_TURQUOISE, DARK_BLUE, PRIMARY_VIOLET}};
	pal[3] = (t_palette){5, 0, {BACKGROUND_SURFACE, DARK_BLUE, DARK_VIOLET, DARK_TURQUOISE, PRIMARY_VIOLET}};
	pal[4] = (t_palette){5, 0, {BACKGROUND_SURFACE,PRIMARY_VIOLET, DARK_BLUE, DARK_VIOLET, DARK_TURQUOISE}};
	pal[5] = (t_palette){7, 0, {VIOLET, BLUE, LIGHT_BLUE, GREEN, YELLOW, ORANGE, RED}};
	pal[fractol->color].cycle = (fractol->cycle) ? 10 : 0;

	if (p.k == fractol->k)
		return (0x000000);
	return (linear_color(p.k, &pal[fractol->color]));
}
