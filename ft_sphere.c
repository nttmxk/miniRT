/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:36:18 by jinoh             #+#    #+#             */
/*   Updated: 2022/08/07 20:36:19 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/ft_math.h"

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
	c = s2_vec(oc) - sp->dia * sp->dia / 4;
	disc = b * b - a * c;
	if (disc < 0)
		return ;
	sol = (-b - sqrt(disc)) / a;
	if (!(sol >= rec->tmin && sol < rec->tmax))
	{
		sol = (-b + sqrt(disc)) / a;
		if (!(sol >= rec->tmin && sol < rec->tmax))
			return ;
	}
	rec->tmax = sol;
	rec->t = sol;
	rec->p = ray_at(ray, sol);
	rec->albedo = sp->color;
	rec->n = vdivide(vminus(rec->p, sp->point), sp->dia / 2);
}
