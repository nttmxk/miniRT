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

#include "includes/minirt.h"
#include "includes/ft_math.h"

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_color	diffuse;
	t_vec	light_dir;
	double	kd;
	t_color	specular;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	double	ksn;
	double	ks;

	light_dir = vunit(vminus(light->point, scene->rec.p));
	kd = fmax(vdot(scene->rec.n, light_dir), 0.0);
	diffuse = vsmul(light->color, kd * light->bright);
	view_dir = vunit(vsmul(scene->ray.dir, -1));
	reflect_dir = reflect(vsmul(light_dir, -1), scene->rec.n);
	ksn = 60;
	ks = 0.5;
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vsmul(vsmul(light->color, ks * light->bright), spec);
	return (vplus(diffuse, specular));
}

t_vec	reflect(t_vec v, t_vec n)
{
	return (vminus(v, vsmul(n, 2 * vdot(v, n))));
}

int	lighting(t_scene *scene)
{
	t_color		light_color;

	if (scene->rec.tmax > 9999998)
		return (get_color(make_color(0, 0, 0)));
	light_color = make_color(0, 0, 0);
	light_color = vplus(light_color,
			point_light_get(scene, &scene->light));
	light_color = vplus(light_color,
			vsmul(scene->ambient.color, scene->ambient.ratio));
	return (get_color(
			vmin(vmul(light_color, scene->rec.albedo),
				make_color(1, 1, 1))));
}
