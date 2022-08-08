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

void	set_face_normal(t_ray *ray, t_rec *rec)
{
	if (vdot(ray->dir, rec->n) > 0)
		rec->n = vsmul(rec->n, -1);
}

t_point	ray_at(t_ray *ray, double t)
{
	return (vplus(ray->orig, vsmul(ray->dir, t)));
}

int	get_color(t_color c)
{
	return (((int)(c.x * 255) << 16) +
	((int)(c.y * 255) << 8) + (int)(c.z * 255));
}

int	color_obj(t_scene *scene, t_objects *ob)
{
	check_hit(ob, &scene->ray, &scene->rec);
	set_face_normal(&scene->ray, &scene->rec);
	return (lighting(scene, ob));
}

void	check_hit(t_objects *ob, t_ray *ray, t_rec *rec)
{
	int	i;

	i = -1;
	while (++i < ob->sp)
		hit_sphere(&ob->spheres[i], ray, rec);
	i = -1;
	while (++i < ob->pl)
		hit_plane(&ob->planes[i], ray, rec);
	i = -1;
	while (++i < ob->cy)
		hit_cylinder(&ob->cylinders[i], ray, rec);
}
