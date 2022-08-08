/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:25:07 by jinoh             #+#    #+#             */
/*   Updated: 2022/08/01 13:25:08 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/ft_math.h"

t_point	ray_at(t_ray *ray, double t)
{
	return (vplus(ray->orig, vsmul(ray->dir, t)));
}

int get_color(t_color c)
{
	return (((int)(c.x * 255) << 16) + ((int)(c.y * 255) << 8) + (int)(c.z * 255));
}

int color_obj(t_scene *scene, t_objects *ob)
{
	int 	i;

	// hit_sphere
	i = -1;
	while (++i < ob->sp)
		hit_sphere(&ob->spheres[i], &scene->ray, &scene->rec);
	// hit_plane
	i = -1;
	while (++i < ob->pl) // delete later
		ob->planes[i].dir = vunit(ob->planes[i].dir);
	i = -1;
	while (++i < ob->pl)
		hit_plane(&ob->planes[i], &scene->ray, &scene->rec);
	// hit_cylinder
	i = -1;
	while (++i < ob->cy)
		hit_cylinder(&ob->cylinders[i], &scene->ray, &scene->rec);
	return (lighting(scene));
}