/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:43:41 by jinoh             #+#    #+#             */
/*   Updated: 2022/08/05 21:43:48 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/ft_math.h"

void	hit_plane(t_plane *pl, t_ray *ray, t_rec *rec)
{
	double	numerator;
	double	denominator;
	double	sol;

	denominator = vdot(ray->dir, pl->dir);
	if (fabs(denominator) < EPSILON)
		return ;
	numerator = vdot(vminus(pl->point, ray->orig), pl->dir);
	sol = numerator / denominator;
	if (sol < rec->tmin || rec->tmax <= sol)
		return ;
	rec->tmax = sol;
	rec->t = sol;
	rec->p = ray_at(ray, sol);
	rec->n = pl->dir;
	rec->albedo = pl->color;
//	set_face_normal(ray, rec);
}
