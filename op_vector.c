/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:23:15 by jinoh             #+#    #+#             */
/*   Updated: 2022/07/30 15:23:16 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_math.h"

double	s2_vec(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	len_vec(t_vec vec)
{
	return (sqrt(s2_vec(vec)));
}

double	dot_vec(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	plus_vec(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec	minus_vec(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec	mul_vec(t_vec a, t_vec b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec	mul_vec_s(t_vec vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

t_vec	divide_vec_s(t_vec vec, double t)
{
	vec.x /= t;
	vec.y /= t;
	vec.z /= t;
	return (vec);
}

t_vec	cross_vec(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x + b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}

t_vec	unit_vec(t_vec vec)
{
	double	len;

	len = len_vec(vec);
	vec.x /= len; // should we consider divided by 0?
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec	min_vec(t_vec a, t_vec b)
{
	if (a.x > b.x)
		a.x = b.x;
	if (a.y > b.y)
		a.y = b.y;
	if (a.z > b.z)
		a.z = b.z;
	return (a);
}
