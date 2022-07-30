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

/*
 * 	idea
 * 		[] convention(func name, estimated time, etc...)
 * 		[]
 */
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
	ray.dir = unit_vec(vec);
	return (ray);
}
