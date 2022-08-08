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

#include "minirt.h"
#include "ft_math.h"

void	hit_sphere(t_sphere *sp, t_ray *ray, t_rec *rec)
{
	t_vec	oc;
	t_disc	d;
	double	sol;

	oc = vminus(ray->orig, sp->point);
	d.a = s2_vec(ray->dir);
	d.b = vdot(oc, ray->dir);
	d.c = s2_vec(oc) - sp->dia * sp->dia / 4;
	d.disc = d.b * d.b - d.a * d.c;
	if (d.disc < 0)
		return ;
	sol = (-d.b - sqrt(d.disc)) / d.a;
	if (!(sol >= rec->tmin && sol < rec->tmax))
	{
		sol = (-d.b + sqrt(d.disc)) / d.a;
		if (!(sol >= rec->tmin && sol < rec->tmax))
			return ;
	}
	rec->tmax = sol;
	rec->t = sol;
	rec->p = ray_at(ray, sol);
	rec->albedo = sp->color;
	rec->n = vdivide(vminus(rec->p, sp->point), sp->dia / 2);
}
