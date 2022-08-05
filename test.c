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

#include "includes/minirt.h"
#include "includes/ft_math.h"

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

int get_color(t_color c)
{
	return (((int)(c.x * 255) << 16) + ((int)(c.y * 255) << 8) + (int)(c.z * 255));
}

void	scene_init_for_temp(t_scene *scene)
{
	double		ka;
	t_object	*obj;//, *obj2;
	t_light		*light;//, *light2;

	ka = 0.3;
	scene->rec.tmax = 99999;
	scene->rec.tmin = 1e-6;
	scene->rec.albedo = make_color(0.7, 0, 0);
	scene->ambient = make_color(ka, ka, ka);
	obj = malloc(sizeof(t_object));
//	obj2 = malloc(sizeof(t_object));
	light = malloc(sizeof(t_light));
//	light2 = malloc(sizeof(t_light));
	scene->light = obj;
	obj->type = LIGHT;
	obj->element = light;
	obj->next = NULL;
//	obj->next = obj2;
//	obj2->type = LIGHT;
//	obj2->element = light2;
//	obj2->next = NULL;

	light->point = make_point(10, 10, -10);
	light->color = make_color(1, 1, 1);

//	light2->color = make_color(1, 1, 1);
//	light2->bright = 1;
//	light2->point = make_point(0, 0, -10);
}

int color_sphere(t_sphere *sp, t_ray *ray)
{
	t_scene scene;
	double 	t;

	scene_init_for_temp(&scene);
	if (hit_sphere(sp, ray, &scene.rec))
		return (lighting(&scene));
//		return (get_color(mul_vec_s(make_color(scene.rec.n.x + 1, scene.rec.n.y + 1, scene.rec.n.z + 1), 0.5)));
	else
	{
		t = 0.5 * (scene.ray.dir.y + 1.0);
//		return (get_color(plus_vec(
//					mul_vec_s(make_color(1, 1, 1), 1.0 - t),
//					mul_vec_s(make_color(0.5, 0.7, 1.0), t))));
		return (SKYBLUE);
	}
}