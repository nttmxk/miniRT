/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 22:57:17 by jinoh             #+#    #+#             */
/*   Updated: 2022/08/05 22:57:19 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/ft_math.h"

static int		check_height(t_cylinder *cy, t_point p);
static t_vec	get_cylinder_n(t_cylinder *cy, t_point p);
static void		hit_cylinder_circle(t_cylinder *cy,
					t_ray *ray, t_rec *rec, double dir);
static void		hit_cylinder_s(t_cylinder *cy, t_ray *ray, t_rec *rec);

void	hit_cylinder(t_cylinder *cy, t_ray *ray, t_rec *rec)
{
	hit_cylinder_circle(cy, ray, rec, 1);
	hit_cylinder_circle(cy, ray, rec, -1);
	hit_cylinder_s(cy, ray, rec);
}

static void	hit_cylinder_s(t_cylinder *cy, t_ray *ray, t_rec *rec)
{
	t_vec	p;
	t_disc	d;
	double	sol;

	p = vminus(ray->orig, cy->point);
	d.a = s2_vec(vcross(ray->dir, cy->dir));
	d.b = vdot(vcross(ray->dir, cy->dir), vcross(p, cy->dir));
	d.c = s2_vec(vcross(p, cy->dir)) - ((cy->dia * cy->dia) / 4);
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
	if (!check_height(cy, ray_at(ray, sol)))
		return ;
	rec->tmax = sol;
	rec->t = sol;
	rec->p = ray_at(ray, sol);
	rec->albedo = cy->color;
	rec->n = get_cylinder_n(cy, rec->p);
}

static void	hit_cylinder_circle(t_cylinder *cy,
							t_ray *ray, t_rec *rec, double dir)
{
	t_point	f;
	t_point	p;
	double	numerator;
	double	t;

	if (fabs(vdot(ray->dir, cy->dir)) < EPSILON)
		return ;
	f = vplus(cy->point, vsmul(cy->dir, cy->height * dir / 2));
//	f = vplus(cy->point, vsmul(cy->dir, cy->height * dir));
	numerator = vdot(vminus(f, ray->orig), vsmul(cy->dir, dir));
	t = numerator / vdot(ray->dir, vsmul(cy->dir, dir));
	if (t < rec->tmin || t >= rec->tmax)
		return ;
	p = vplus(ray->orig, vsmul(ray->dir, t));
	if (vlen(vminus(f, p)) > cy->dia / 2)
		return ;
	rec->t = t;
	rec->p = p;
	rec->tmax = t;
	rec->n = vsmul(cy->dir, dir);
	rec->albedo = cy->color;
}

static int	check_height(t_cylinder *cy, t_point p)
{
	double	hit_height;

	hit_height = vdot(vminus(p, cy->point), cy->dir);
	if (fabs(hit_height) > cy->height / 2)
		return (0);
//	if (fabs(hit_height) > cy->height)
//		return (0);
	return (1);
}

static t_vec	get_cylinder_n(t_cylinder *cy, t_point p)
{
	t_vec	hit_height;

	hit_height = vsmul(cy->dir, vdot(vminus(p, cy->point), cy->dir));
	return (vdivide(vminus(p, vplus(cy->point, hit_height)), cy->dia / 2));
}
