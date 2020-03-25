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

void			*calculation(void *threadarg)
{
	t_thread	*my_data;
	int	x;
	int y;
	const ft_fract func_array[] = {julia, mandelbrot, unnamed1, unnamed2};

	my_data = (t_thread *)threadarg;
	y = my_data->fractol->picture->height / NUM_PROC * my_data->thread_id;
	while (y < my_data->fractol->picture->height /NUM_PROC * (my_data->thread_id + 1))
	{
		x = 0;
		while (x < my_data->fractol->picture->width)
		{
			my_data->fractol->pixel_data[y *my_data->fractol->picture->width + x] = func_array[my_data->fractol->fract](x, y, my_data->fractol);
			x++;
		}
		y++;
	}
	return (NULL);
}

void			init_threads(t_fractol *fractol)
{
	int			i;
	t_process	*p;

	p = &fractol->process;
	i = 0;
	while (i < NUM_PROC)
	{
		p->threads_data[i].thread_id = i;
		p->threads_data[i].fractol = fractol;
		if (pthread_create(p->threads + i, NULL, calculation, &(p->threads_data[i])))
			error("ERROR; return code from pthread_create()\n");
		i++;
	}
	i = 0;
	while (i < NUM_PROC)
	{
		pthread_join(p->threads[i], NULL);
		i++;
	}
}

void			draw(t_fractol *fractol)
{
	int		i;
	int		j;

	init_threads(fractol);
	j = 0;
	while (j < fractol->picture->height)
	{
		i = 0;
		while (i < fractol->picture->width)
		{
			put_pixel(fractol->picture, new_point(i, j, get_linear_color(fractol->pixel_data[j * fractol->picture->width + i], fractol)));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(fractol->picture->mlx, fractol->picture->win, fractol->picture->img, 0, 0);
}
