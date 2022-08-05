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
	diffuse = mul_vec_s(light->color, kd);

	view_dir = unit_vec(mul_vec_s(scene->ray.dir, -1));
	reflect_dir = reflect(light_dir, scene->rec.n);
	ksn = 30;
	ks = 0.8;
	spec = pow(fmax(dot_vec(view_dir, reflect_dir), 0.0), ksn);
	specular = mul_vec_s(mul_vec_s(light->color, ks), spec);

	return (plus_vec(diffuse, specular));
}

t_vec	reflect(t_vec v, t_vec n)
{
	return (plus_vec(
			mul_vec_s(v, -1),
			mul_vec_s(n, 2 * dot_vec(v, n))
		));
}

int	lighting(t_scene *scene)
{
	t_color		light_color;
	t_object	*lights;

	light_color = make_color(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT)
			light_color = plus_vec(light_color,
					point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = plus_vec(light_color, scene->ambient);
	free(scene->light->element); ////// for test
	free(scene->light);
	return (get_color(
			min_vec(mul_vec(light_color, scene->rec.albedo),
				make_color(1, 1, 1))));
}
