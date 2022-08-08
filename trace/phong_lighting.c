/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <jinoh@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:37:52 by julien            #+#    #+#             */
/*   Updated: 2022/08/05 16:37:56 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_math.h"

t_color	point_light_get(t_scene *scene, t_light *light, t_objects *ob)
{
	t_phong_light	pl;

	pl.light_dir = vminus(light->point, scene->rec.p);
	pl.light_ray = make_ray(vplus(scene->rec.p,
				vsmul(scene->rec.n, EPSILON)), pl.light_dir);
	if (in_shadow(ob, &pl.light_ray, scene->rec, vlen(pl.light_dir)))
		return (make_color(0, 0, 0));
	pl.light_dir = vunit(pl.light_dir);
	pl.kd = fmax(vdot(scene->rec.n, pl.light_dir), 0.0);
	pl.diffuse = vsmul(light->color, pl.kd * light->bright);
	pl.view_dir = vunit(vsmul(scene->ray.dir, -1));
	pl.reflect_dir = reflect(vsmul(pl.light_dir, -1), scene->rec.n);
	pl.ksn = 60;
	pl.ks = 0.5;
	pl.spec = pow(fmax(vdot(pl.view_dir, pl.reflect_dir), 0.0), pl.ksn);
	pl.specular = vsmul(vsmul(light->color, pl.ks * light->bright), pl.spec);
	return (vplus(pl.diffuse, pl.specular));
}

t_vec	reflect(t_vec v, t_vec n)
{
	return (vminus(v, vsmul(n, 2 * vdot(v, n))));
}

int	lighting(t_scene *scene, t_objects *ob)
{
	t_color		light_color;

	if (scene->rec.tmax > TMAX - 1)
		return (get_color(make_color(0, 0, 0)));
	light_color = make_color(0, 0, 0);
	light_color = vplus(light_color,
			point_light_get(scene, &scene->light, ob));
	light_color = vplus(light_color,
			vsmul(scene->ambient.color, scene->ambient.ratio));
	return (get_color(
			vmin(vmul(light_color, scene->rec.albedo),
				make_color(1, 1, 1))));
}

int	in_shadow(t_objects *ob, t_ray *ray, t_rec rec, double light_len)
{
	rec.tmax = light_len;
	check_hit(ob, ray, &rec);
	if (rec.tmax < light_len - EPSILON)
		return (1);
	return (0);
}
