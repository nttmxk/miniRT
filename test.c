/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:25:07 by jinoh             #+#    #+#             */
/*   Updated: 2022/08/01 13:25:08 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vec(t_vec vec)
{
	printf("%f %f %f\n", vec.x, vec.y, vec.z);
}

t_point	ray_at(t_ray *ray, double t)
{
	return (plus_vec(ray->orig, mul_vec_s(ray->dir, t)));
}

int	hit_sphere(t_sphere *sp, t_ray *ray, t_rec *rec)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sol;

	oc = minus_vec(ray->orig, sp->point);
	a = s2_vec(ray->dir);
	b = dot_vec(oc, ray->dir);
	c = s2_vec(oc) - sp->dia * sp->dia;
	disc = b * b - a * c;
	if (disc < 0)
		return (0);
	sol = (-b - sqrt(disc)) / a;
	if (!(sol >= rec->tmin && sol <= rec->tmax))
	{
		sol = (-b + sqrt(disc)) / a;
		if (!(sol >= rec->tmin && sol <= rec->tmax))
			return (0);
	}
	rec->t = sol;
	rec->p = ray_at(ray, sol);
	rec->n = divide_vec_s(minus_vec(rec->p, sp->point) , sp->dia);
	return (1);
}

t_camera	make_cam(void)
{
	t_camera	cam;

	cam.orig = make_point(0, 0, 10);
	cam.dir = make_vec(0, 0, -1);
	cam.left = minus_vec(
			minus_vec(cam.orig,
				plus_vec(
					divide_vec_s(make_vec(WIN_WIDTH, 0, 0), 2),
					divide_vec_s(make_vec(0, WIN_HEIGHT, 0), 2)
					)),
			make_vec(0, 0, 100));
	return (cam);
}

int get_color(t_color c)
{
	return (((int)(c.x * 255) << 16) + ((int)(c.y * 255) << 8) + (int)(c.z * 255));
}

void	scene_init(t_scene *scene)
{
	double ka;

	ka = 0.1;
	scene->ambient = make_color(ka, ka, ka);
}

void	rec_init(t_rec *rec)
{
	rec->tmax = 999999;
	rec->tmin = 1e-6;
}

int color_sphere(t_sphere *sp, t_ray *ray)
{
	t_rec	rec;

	rec_init(&rec);
	if (hit_sphere(sp, ray, &rec))
		return (get_color(mul_vec_s(make_color(rec.n.x + 1, rec.n.y + 1, rec.n.z + 1), 0.5)));
	else
		return (SKYBLUE);
}

int	lighting(t_scene *scene)
{
	t_color		light_color;
	t_object	*lights;

	light_color = make_color(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT)
			light_color = plus_vec(light_color, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = plus_vec(light_color, scene->ambient);
//	return (get_color(
//			min_vec(
//				mul_vec(light_color, scene->rec.albedo),
//				make_color(1, 1, 1))
//						));
	return (0);
}

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_color	diffuse;
	t_vec	light_dir;
	double	kd = 0;

//	light_dir = unit_vec(minus_vec(light->point, scene->rec.p));
//	kd = fmax(dot_vec(scene->rec.n, light_dir), 0.0);
	diffuse = mul_vec_s(light->color, kd);
	return (diffuse);
}
