#include "minirt.h"
#include "ft_math.h"

void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	hit_sphere(t_sphere sp, t_ray ray);
int	get_color(int iter, int shift_color);
int loop_func(t_data *data);

int main()
{
	t_data data;

	data_init(&data);
	mlx_loop_hook(data.mlx, loop_func, &data);
	mlx_loop(data.mlx);
}

int loop_func(t_data *data)
{
	int x;
	int y;
	t_sphere	sp;
	t_ray		ray;

	x = -1;
	sp.point = make_point(9999, -25, -25);
	sp.dia = 0.2;
	ray = make_ray(make_point(0, 0, 0), make_vec(1, 1, 1));
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			if (hit_sphere(sp, ray))
				my_mlx_pixel_put(data, x, y, get_color(70, data->color));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "fractal");
	if (!data->win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit(1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
								   &data->line_length, &data->endian);
	if (!data->addr)
		exit(1);
	data->x = 0;
	data->y = 0;
	data->press_f = 0;
	data->color = 0;
	data->zoom_rate = 1;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * (data->bpp / 8)) + (y * data->line_length);
	*(unsigned int *)dst = color;
}

int	get_color(int iter, int shift_color)
{
	int		color;
	double	r;

	r = (double)iter / ITER_MAX;
	color = 0;
	color += (int)(8.5 * pow(1 - r, 3) * 255 * r) << 16;
	color += (int)(15 * pow(1 - r, 2) * pow(r, 2) * 255) << 8;
	color += (int)(9 * (1 - r) * pow(r, 3) * 255);
	if (shift_color == 1)
		color = ((color & 0xFF0000) >> 16)
				+ ((color & 0x00FF00) << 8)
				+ ((color & 0x0000FF) << 8);
	else if (shift_color == 2)
		color = ((color & 0xFF0000) >> 8)
				+ ((color & 0x00FF00) >> 8)
				+ ((color & 0x0000FF) << 16);
	return (color);
}


int	hit_sphere(t_sphere sp, t_ray ray)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = minus_vec(ray.orig, sp.point);
	a = dot_vec(ray.dir, ray.dir);
	b = 2.0 * dot_vec(oc, ray.dir);
	c = dot_vec(oc, oc) - sp.dia * sp.dia;
	disc = b * b - 4 * a * c;
	return (disc > 0);
}