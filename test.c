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
	return (vplus(ray->orig, vsmul(ray->dir, t)));
}

void	hit_sphere(t_sphere *sp, t_ray *ray, t_rec *rec)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sol;

	oc = vminus(ray->orig, sp->point);
	a = s2_vec(ray->dir);
	b = vdot(oc, ray->dir);
	c = s2_vec(oc) - sp->dia * sp->dia;
	disc = b * b - a * c;
	if (disc < 0)
		return ;
	sol = (-b - sqrt(disc)) / a;
	if (!(sol >= rec->tmin && sol <= rec->tmax))
	{
		sol = (-b + sqrt(disc)) / a;
		if (!(sol >= rec->tmin && sol <= rec->tmax))
			return ;
	}
	if (sol < rec->tmax)
	{
		rec->tmax = sol;
		rec->t = sol;
		rec->p = ray_at(ray, sol);
		rec->albedo = sp->color;
		rec->n = vdivide(vminus(rec->p, sp->point), sp->dia);
	}
}


int get_color(t_color c)
{
	return (((int)(c.x * 255) << 16) + ((int)(c.y * 255) << 8) + (int)(c.z * 255));
}

//void	scene_init_for_temp(t_scene *scene)
//{
//	double		ka;
//	t_object	*obj;
//	t_light		*light;
//	t_object	*ob, *ob2;
//	t_sphere	*sp, *sp2;
//
//	sp = malloc(sizeof(t_sphere));
//	sp2 = malloc(sizeof(t_sphere));
//	sp->point = make_point(25, 0, -30);
//	sp->dia = 25;
//	sp2->point = make_point(-25, 0, -30);
//	sp2->dia = 25;
//	ob = malloc(sizeof(t_object));
//	ob2 = malloc(sizeof(t_object));
//
//	scene->map = ob;
//	ob->element = sp;
//	ob->type = SP;
//	ob->next = ob2;
//	ob2->element = sp2;
//	ob2->next = NULL;
//	ob2->type = SP;
//
//	scene->camera = make_cam();
//
//	ka = 0.3;
//	scene->rec.albedo = make_color(0.7, 0, 0);
//	scene->ambient = make_color(ka, ka, ka);
//	obj = malloc(sizeof(t_object));
//	light = malloc(sizeof(t_light));
//	scene->light = obj;
//	obj->type = LIGHT;
//	obj->element = light;
//	obj->next = NULL;
//	light->point = make_point(10, 1000, -10);
//	light->color = make_color(1, 1, 1);
//}

int color_sphere(t_scene *scene, t_objects *obj)
{
	double	t;
	int 	i;

	// hit_sphere
	i = -1;
	while (++i < obj->sp)
		hit_sphere(&obj->spheres[i], &scene->ray, &scene->rec);
	// hit_plane
//	i = -1;
//	while (++i < obj->pl)
//		hit_plane(&obj->spheres[i], &scene->ray, &scene->rec);
	// hit_cylinder
//	i = -1;
//	while (++i < obj->cy)
//		hit_cylinder(&obj->spheres[i], &scene->ray, &scene->rec);;;

	return (lighting(scene));
}