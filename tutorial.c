#include "minirt.h"
#include "mlx.h"

void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		loop_func(t_data *data);
int		press_key(int key, void *p);

int main()
{
//	cc -lmlx -framework OpenGL -framework AppKit *.c
	t_data data;

	data_init(&data);
	mlx_key_hook(data.win, press_key, &data);
	mlx_loop_hook(data.mlx, loop_func, &data);
	mlx_loop(data.mlx);
}

int loop_func(t_data *data)
{
	int x;
	int y;
	double u, v;
	t_sphere	sp;
	t_ray		ray;
	t_camera	cam;

	sp.point = make_point(0, 0, -30);
	sp.dia = 25;
	cam = make_cam();
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			u = (double)x / (WIN_WIDTH - 1);
			v = (double)y / (WIN_HEIGHT - 1);
			ray = make_view(&cam, u, v);
			my_mlx_pixel_put(data, x, y, color_sphere(&sp, &ray));
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