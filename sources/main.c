/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/30 16:28:48 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	error("Usage: ./fractol NAME_OF_FRACTAL\n"
	"NAME_OF_FRACTAL:\n"
	"    ->Julia\n"
	"    ->Mandelbrot\n"
	"    ->Heart\n"
	"    ->Mystery\n"
	"    ->Unnamed\n");
}

int		find_fractal(char *argv)
{
	if (!ft_strcmp(argv, "Julia") || !ft_strcmp(argv, "julia"))
		return (JULIA);
	if (!ft_strcmp(argv, "Mandelbrot") || !ft_strcmp(argv, "mandelbrot"))
		return (MANDELBROT);
	if (!ft_strcmp(argv, "Heart") || !ft_strcmp(argv, "heart"))
		return (HEART);
	if (!ft_strcmp(argv, "Mystery") || !ft_strcmp(argv, "mystery"))
		return (MYSTERY);
	if (!ft_strcmp(argv, "Unnamed") || !ft_strcmp(argv, "unnamed"))
		return (UNNAMED);
	return (-1);
}

int		main(int argc, char **argv)
{
	t_fractol	*fractol;
	t_picture	*picture;
	int			name;

	if (argc != 2)
		print_usage();
	if ((name = find_fractal(argv[1])) == -1)
		error("Please, give me existed fractal...\n");
	if (!(picture = picture_init("Fract'ol", WIDTH, HEIGHT)))
		error("Picture couldn't initialize...\n");
	if (!(fractol = fractol_init(picture, name)))
		error("Fractol couldn't initialize...\n");
	draw(fractol);
	mlx_hooks(fractol);
	mlx_loop(picture->mlx);
	return (0);
}
