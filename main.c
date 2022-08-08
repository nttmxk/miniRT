#include "includes/minirt.h"
#include "includes/ft_math.h"
#include "mlx.h"

void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		loop_func(t_data *data);
int		press_key(int key);
int		red_button(int exitcode);

int	main(int ac, char **av)
{
	t_data data = {0};

	if (ac != 2)
		return (1); // error
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
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			u = (double)x / (WIN_WIDTH - 1);
			v = (double)y / (WIN_HEIGHT - 1);
			scene->ray = make_view(&scene->camera, u, v);
			data->scene.rec.tmax = TMAX;
			data->scene.rec.tmin = EPSILON;
			my_mlx_pixel_put(data, x,  WIN_HEIGHT - y - 1, color_obj(scene, &data->objects));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

t_vec	cam_set_vup(t_vec dir)
{
	if (dir.x == 0 && dir.y != 0 && dir.z == 0)
		return (make_vec(0, dir.y, 1e-6));
	else
		return (make_vec(0, 1, 0));
}

void	camera_init(t_camera *camera)
{
	t_vec		w;
	t_vec		u;
	t_vec		v;
	t_vec		updir;

	camera->focal_len = tan((camera->fov * PI / 180.0) / 2.0);
	camera->viewport_h = camera->focal_len * 2;
	camera->viewport_w = camera->viewport_h * ((double)WIN_WIDTH / (double)WIN_HEIGHT);
	camera->dir = vunit(camera->dir);
	updir = cam_set_vup(camera->dir);
	w = vunit(vsmul(camera->dir, -1));
	u = vunit(vcross(cam_set_vup(camera->dir), w));
	v = vcross(w, u);
	camera->horizontal = vsmul(u, camera->viewport_w);
	camera->vertical = vsmul(v, camera->viewport_h);
	camera->left = vminus(vminus(vminus(camera->orig,
										vdivide(camera->horizontal, 2)),
								 vdivide(camera->vertical, 2)), w);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	camera_init(&data->scene.camera);
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

int	press_key(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		red_button(int exitcode)
{
	exit(exitcode);
}
