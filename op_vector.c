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

#include "ft_math.h"

inline double	s2_vec(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z + vec.z);
}

inline double	len_vec(t_vec vec)
{
	return (sqrt(s2_vec(vec)));
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

t_vec	mul_vecs(t_vec vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

t_vec	divide_vecs(t_vec vec, double t)
{
	vec.x /= t;
	vec.y /= t;
	vec.z /= t;
	return (vec);
}

inline double	dot_vec(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y + b.y + a.z + b.z);
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
