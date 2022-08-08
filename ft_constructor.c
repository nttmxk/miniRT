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

#include "includes/minirt.h"
#include "includes/ft_math.h"

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
	t_vec	horizontal;
	t_vec	vertical;

	ray.orig = cam->orig;
	/////////// just for test
	horizontal = make_vec(WIN_WIDTH, 0, 0);
	vertical = make_vec(0, WIN_HEIGHT, 0);
	//////////
	ray.dir = vunit(
			vminus(
				vplus(
					vplus(
						vsmul(horizontal, u), vsmul(vertical, v)),
					cam->left),
				cam->orig));
	return (ray);
}
