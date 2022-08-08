/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_constructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:22:59 by jinoh             #+#    #+#             */
/*   Updated: 2022/07/30 15:23:02 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_math.h"

t_vec	make_vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point	make_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color	make_color(double x, double y, double z)
{
	t_color	color;

	color.x = x;
	color.y = y;
	color.z = z;
	return (color);
}

t_ray	make_ray(t_point p, t_vec vec)
{
	t_ray	ray;

	ray.orig = p;
	ray.dir = vunit(vec);
	return (ray);
}

t_ray	make_view(t_camera *cam, double u, double v)
{
	t_ray	ray;
	static int i;
	ray.orig = cam->orig;
	/////////// just for test
//	t_vec horizontal = make_vec(WIN_WIDTH, 0, 0);
//	t_vec vertical = make_vec(0, WIN_HEIGHT, 0);
	//////////
	ray.dir = vunit(vminus(vplus(vplus(cam->left,
									   vsmul(cam->horizontal, u)),
								 vsmul(cam->vertical, v)),
						   cam->orig));
//	ray.dir = vunit(
//			vminus(
//				vplus(
//					vplus(cam->left, vsmul(cam->horizontal, u)), vsmul(cam->vertical, v)),
//				cam->orig));
	if (i == 0) {
		++i;
		printf("rayorig: %f, %f, %f\n", ray.orig.x, ray.orig.y, ray.orig.z);
		printf("raydir: %f, %f, %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
		printf("%p\n", cam);
		printf("cam left: %f, %f, %f\n", cam->left.x, cam->left.y, cam->left.z);
		printf("cam orig: %f, %f, %f\n", cam->orig.x, cam->orig.y, cam->orig.z);
		printf("cam horizontal: %f, %f, %f\n", cam->horizontal.x, cam->horizontal.y, cam->horizontal.z);
		printf("cam vertical: %f, %f, %f\n", cam->vertical.x, cam->vertical.y, cam->vertical.z);
	}
	return (ray);
}

/*
t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom,
						vmult(cam->horizontal, u)),
					vmult(cam->vertical, v)),
				cam->orig));
	return (ray);
}*/
