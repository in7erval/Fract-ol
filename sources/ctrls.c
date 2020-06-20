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

void	move(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_UP)
		fractol->offset.y -= (fractol->z_max.y - fractol->z_min.y)
							* fractol->zoom * 0.05;
	if (keycode == KEY_DOWN)
		fractol->offset.y += (fractol->z_max.y - fractol->z_min.y)
							* fractol->zoom * 0.05;
	if (keycode == KEY_LEFT)
		fractol->offset.x -= (fractol->z_max.x - fractol->z_min.x)
							* fractol->zoom * 0.05;
	if (keycode == KEY_RIGHT)
		fractol->offset.x += (fractol->z_max.x - fractol->z_min.x)
							* fractol->zoom * 0.05;
}

void	zoom_or_move(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_PLUS)
		zoom(fractol->picture->width / 2, fractol->picture->height / 2,
	fractol, 1 / ZOOM);
	if (keycode == KEY_MINUS)
		zoom(fractol->picture->width / 2, fractol->picture->height / 2,
	fractol, ZOOM);
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT)
		move(keycode, fractol);
}

void	mlx_hooks(t_fractol *fractol)
{
	mlx_hook(fractol->picture->win, 17, 0, exit_program, fractol);
	mlx_hook(fractol->picture->win, 2, 0, deal_key, fractol);
	mlx_hook(fractol->picture->win, 4, 0, mouse_press, fractol);
	mlx_hook(fractol->picture->win, 5, 0, mouse_release, fractol);
	mlx_hook(fractol->picture->win, 6, 0, mouse_move, fractol);
}

int		deal_key(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS || keycode == KEY_UP
		|| keycode == KEY_DOWN || keycode == KEY_LEFT || keycode == KEY_RIGHT)
		zoom_or_move(keycode, fractol);
	if (keycode >= KEY_1_UP && keycode <= KEY_5_UP)
		color(keycode, fractol);
	if (keycode == KEY_C)
		fractol->cycle = (fractol->cycle == 1) ? 0 : 1;
	if (keycode == KEY_R)
		reset(fractol);
	if (keycode == KEY_W && fractol->k < 1000)
		fractol->k++;
	if (keycode == KEY_S && fractol->k > 0)
		fractol->k--;
	if (keycode == KEY_D)
		fractol->r -= 0.1;
	if (keycode == KEY_E)
		fractol->r += 0.1;
	draw(fractol);
	return (keycode);
}
