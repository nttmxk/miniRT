/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:30:19 by hakim             #+#    #+#             */
/*   Updated: 2022/08/08 18:30:20 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/ft_math.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		loop_func(t_data *data);
int		press_key(int key);
int		red_button(int exitcode);

int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){0};
	if (ac != 2)
	{
		printf("Error\nUsage: ./miniRT scene_file.rt\n");
		return (1);
	}
	parse_mini_rt(av[1], &data);
	data_init(&data);
	mlx_key_hook(data.win, press_key, &data);
	mlx_hook(data.win, 17, 0, red_button, 0);
	mlx_loop_hook(data.mlx, loop_func, &data);
	mlx_loop(data.mlx);
	return (0);
}

int	loop_func(t_data *data)
{
	int		x;
	int		y;
	double	u;
	double	v;
	t_scene	*scene;

	scene = &data->scene;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			u = (double)x / (WIDTH - 1);
			v = (double)y / (HEIGHT - 1);
			scene->ray = make_view(&scene->camera, u, v);
			data->scene.rec.tmax = TMAX;
			data->scene.rec.tmin = EPSILON;
			my_mlx_pixel_put(data, x, HEIGHT - y - 1,
				color_obj(scene, &data->objects));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * (data->bpp / 8)) + (y * data->line_length);
	*(unsigned int *)dst = color;
}

int	press_key(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

int	red_button(int exitcode)
{
	exit(exitcode);
}
