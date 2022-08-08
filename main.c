#include "includes/minirt.h"
#include "includes/ft_math.h"
#include "mlx.h"

void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		loop_func(t_data *data);
int		press_key(int key, void *p);

int	main(int ac, char **av)
{
	t_data data = {0};

	if (ac != 2)
		return (1); // error
	parse_mini_rt(av[1], &data);
	data_init(&data);
	mlx_key_hook(data.win, press_key, &data);
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
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			u = (double)x / (WIN_WIDTH - 1);
			v = (double)y / (WIN_HEIGHT - 1);
			scene->ray = make_view(&scene->camera, u, v);
			data->scene.rec.tmax = 9999999;
			data->scene.rec.tmin = EPSILON;
			my_mlx_pixel_put(data, x,  WIN_HEIGHT - y - 1, color_obj(scene, &data->objects));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->scene.camera.left = vminus(
			vminus(data->scene.camera.orig,
				   vplus(
						   vdivide(make_vec(WIN_WIDTH, 0, 0), 2),
						   vdivide(make_vec(0, WIN_HEIGHT, 0), 2)
				   )),
			make_vec(0, 0, 100));
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data->win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit(1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
								   &data->line_length, &data->endian);
	if (!data->addr)
		exit(1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * (data->bpp / 8)) + (y * data->line_length);
	*(unsigned int *)dst = color;
}

int	press_key(int key, void *p)
{
	if (key == 53)
		exit(0);
	return (0);
}
