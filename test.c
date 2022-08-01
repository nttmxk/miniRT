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

double	hit_sphere(t_sphere *sp, t_ray *ray)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = minus_vec(ray->orig, sp->point);
	a = dot_vec(ray->dir, ray->dir);
	b = dot_vec(oc, ray->dir);
	c = dot_vec(oc, oc) - sp->dia * sp->dia;
	disc = b * b - a * c;
	if (disc < 0)
		return (-1);
	else
		return ((-b - sqrt(disc)) / a);
	// [-b +_ sqrt(disc) / a]. but why we chose small one?
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
