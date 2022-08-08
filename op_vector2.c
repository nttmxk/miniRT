/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:06:06 by jinoh             #+#    #+#             */
/*   Updated: 2022/08/08 15:06:10 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_math.h"

t_vec	vmul(t_vec a, t_vec b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec	vsmul(t_vec vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

t_vec	vdivide(t_vec vec, double t)
{
	vec.x /= t;
	vec.y /= t;
	vec.z /= t;
	return (vec);
}

t_vec	vcross(t_vec a, t_vec b)
{
	t_vec	vec;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}

t_vec	vunit(t_vec vec)
{
	double	len;

	len = vlen(vec);
	vec.x /= len; // should we consider divided by 0?
	vec.y /= len;
	vec.z /= len;
	return (vec);
}
