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

int		exit_program(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	mlx_hooks(t_fractol *fractol)
{
	mlx_hook(fractol->picture->win, 17, 0, exit_program, fractol);
	mlx_hook(fractol->picture->win, 2, 0, deal_key, fractol);
	mlx_hook(fractol->picture->win, 4, 0, mouse_press, fractol);
	mlx_hook(fractol->picture->win, 5, 0, mouse_release, fractol);
	mlx_hook(fractol->picture->win, 6, 0, mouse_move, fractol);
}

void	move(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_UP)
		fractol->offset.y -= (fractol->z_max.y - fractol->z_min.y) * fractol->zoom * 0.05;
	if (keycode == KEY_DOWN)
		fractol->offset.y += (fractol->z_max.y - fractol->z_min.y) * fractol->zoom * 0.05;
	if (keycode == KEY_LEFT)
		fractol->offset.x -=  (fractol->z_max.x - fractol->z_min.x) * fractol->zoom * 0.05;
	if (keycode == KEY_RIGHT)
		fractol->offset.x +=  (fractol->z_max.x - fractol->z_min.x) * fractol->zoom * 0.05;
}

void	color(int keycode, t_fractol *fractol)
{
	if (keycode >= KEY_1_UP && keycode <= KEY_4_UP)
		fractol->color = keycode - 18;
	if (keycode == KEY_5_UP)
		fractol->color = keycode - 19;
	if (keycode == KEY_6_UP)
		fractol->color = keycode - 17;
}

int		deal_key(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_PLUS)
		zoom(WIDTH / 2, HEIGHT / 2, fractol, 1 / ZOOM);
	if (keycode == KEY_MINUS)
		zoom(WIDTH / 2, HEIGHT / 2, fractol, ZOOM);
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT || keycode == KEY_RIGHT)
		move(keycode, fractol);
	if (keycode >= KEY_1_UP && keycode <= KEY_5_UP)
		color(keycode, fractol);
	if (keycode == KEY_C)
		fractol->cycle = (fractol->cycle == 1) ? 0 : 1;
	draw_map(fractol);
	return (keycode);
}
