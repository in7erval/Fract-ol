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

	if (p.k == K)
		return (0x000000);
	return (linear_color(p.k, &pal[fractol->color]));
}

t_pixel	mandelbrot(int x, int y, t_fractol *fractol)
{
	t_complex	zk;
	t_complex	c;
	t_pixel		p;
	t_complex	z;


	z.x = fractol->z_min.x + ((double)x / WIDTH) * (fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->offset.x;
	z.y = fractol->z_min.y + ((double)y / HEIGHT) * (fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->offset.y;
	c = z;
	p.k = 0;
	while ((p.r = z.x * z.x + z.y * z.y) < R && p.k < K)
	{
		zk.x = (z.x + z.y) * (z.x - z.y) + c.x;
		zk.y = z.x * z.y * 2 + c.y;
		if (z.x == zk.x && z.y == zk.y)
		{
			p.k = K;
			break ;
		}
		z.x = zk.x;
		z.y = zk.y;
		p.k++;
	}
	return (p);
}

t_pixel	julia(int x, int y, t_fractol *fractol)
{
	t_complex zk;
	t_pixel p;
	t_complex z;

	z.x = fractol->z_min.x + ((double)x / WIDTH) * (fractol->z_max.x - fractol->z_min.x) * fractol->zoom + fractol->offset.x;
	z.y = fractol->z_min.y + ((double)y / HEIGHT) * (fractol->z_max.y - fractol->z_min.y) * fractol->zoom + fractol->offset.y;
	p.k = 0;
	while (1)
	{
		zk.x = (z.x + z.y) * (z.x - z.y) + fractol->c.x;
		zk.y = 2 * z.x * z.y + fractol->c.y;
		if (!((p.r = zk.x * zk.x + zk.y * zk.y) < R && p.k < K))
			break;
		if (zk.x == z.x && zk.y == z.y)
		{
			p.k = K;
			break;
		}
		z.x = zk.x;
		z.y = zk.y;
		p.k++;
	}
	return (p);
}


void *calc_map(void *threadarg)
{
	int			id;
	t_fractol	*fractol;
	t_thread	*my_data;
	int	x;
	int y;

	my_data = (t_thread *)threadarg;
	id = my_data->thread_id;
	fractol = my_data->fractol;
	y = (HEIGHT / NUM_PROC) * id;
	while (y < (HEIGHT / NUM_PROC) * (id + 1))
	{
		x = 0;
		while (x < WIDTH)
		{
			if (fractol->fract == JULIA)
				fractol->pixel_data[y * WIDTH + x] = julia(x, y, fractol);
			if (fractol->fract == MANDELBROT)
				fractol->pixel_data[y * WIDTH + x] = mandelbrot(x, y, fractol);
			x++;
		}
		y++;
	}
	return (NULL);
}

void			draw_map(t_fractol *fractol)
{
	int			i;
	int			j;
	pthread_t	threads[NUM_PROC];
	t_thread	threads_data[NUM_PROC];

	i = 0;
	while (i < NUM_PROC)
	{
		threads_data[i].thread_id = i;
		threads_data[i].fractol = fractol;
		if (pthread_create(&threads[i], NULL, calc_map, (void *)&threads_data[i]))
			error("ERROR; return code from pthread_create()\n");
		i++;
	}
	i = 0;
	while (i < NUM_PROC)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	ft_bzero(fractol->picture->data_addr, WIDTH * HEIGHT * (fractol->picture->bits_per_pixel / 8));
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			put_pixel(fractol->picture, new_point(i, j, get_linear_color(fractol->pixel_data[j * WIDTH + i], fractol)));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(fractol->picture->mlx, fractol->picture->win, fractol->picture->img, 0, 0);
}
