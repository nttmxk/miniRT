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

int color_sphere(t_sphere *sp, t_ray *ray)
{
	t_rec	rec;

	////////////////////for temp
	rec.tmax = 99999999;
	rec.tmin = 0;
	////////////////////
	if (hit_sphere(sp, ray, &rec))
		return (get_color(mul_vec_s(make_color(rec.n.x + 1, rec.n.y + 1, rec.n.z + 1), 0.5)));
	else
		return (SKYBLUE);
}