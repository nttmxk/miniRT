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

	light_dir = unit_vec(minus_vec(light->point, scene->rec.p));
	kd = fmax(dot_vec(scene->rec.n, light_dir), 0.0);
	diffuse = mul_vec_s(light->color, kd * light->bright);

	view_dir = unit_vec(mul_vec_s(scene->ray.dir, -1));
	reflect_dir = reflect(mul_vec_s(light_dir, -1), scene->rec.n);
	ksn = 60;
	ks = 0.5;
	spec = pow(fmax(dot_vec(view_dir, reflect_dir), 0.0), ksn);
	specular = mul_vec_s(mul_vec_s(light->color, ks * light->bright), spec);

	return (plus_vec(diffuse, specular));
}

t_vec	reflect(t_vec v, t_vec n)
{
	return (minus_vec(v, mul_vec_s(n, 2 * dot_vec(v, n))));
}

int	lighting(t_scene *scene)
{
	t_color		light_color;

	if (scene->rec.tmax > 9999998)
		return (get_color(make_color(0, 0, 0)));
	light_color = make_color(0, 0, 0);
	light_color = plus_vec(light_color,
						   point_light_get(scene, &scene->light));
	light_color = plus_vec(light_color, mul_vec_s(scene->ambient.color, scene->ambient.ratio));
	return (get_color(
			min_vec(mul_vec(light_color, scene->rec.albedo),
				make_color(1, 1, 1))));
}
