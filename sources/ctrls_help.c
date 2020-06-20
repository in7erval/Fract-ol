/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/30 13:42:21 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color(int keycode, t_fractol *fractol)
{
	if (keycode >= KEY_1_UP && keycode <= KEY_4_UP)
		fractol->color = keycode - 18;
	if (keycode == KEY_5_UP)
		fractol->color = keycode - 19;
	if (keycode == KEY_6_UP)
		fractol->color = keycode - 17;
}

void	reset(t_fractol *fractol)
{
	fractol->c.x = 0;
	fractol->c.y = 0;
	fractol->zoom = 1;
	fractol->offset = (t_complex){.x = 0, .y = 0};
	fractol->r = 4;
	fractol->k = 32;
}
