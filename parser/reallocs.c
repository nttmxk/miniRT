/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:44 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:45 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*realloc_sp(t_objects *objects, int sp_count)
{
	t_sphere	*new_spheres;
	int			i;

	new_spheres = malloc(sizeof(t_sphere) * (sp_count + 1));
	if (new_spheres == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < sp_count)
	{
		new_spheres[i] = objects->spheres[i];
		++i;
	}
	if (sp_count != 0)
		free(objects->spheres);
	objects->spheres = new_spheres;
	return (&new_spheres[i]);
}

t_plane	*realloc_pl(t_objects *objects, int pl_count)
{
	t_plane	*new_planes;
	int		i;

	new_planes = malloc(sizeof(t_plane) * (pl_count + 1));
	if (new_planes == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < pl_count)
	{
		new_planes[i] = objects->planes[i];
		++i;
	}
	if (pl_count != 0)
		free(objects->planes);
	objects->planes = new_planes;
	return (&new_planes[i]);
}

t_cylinder	*realloc_cy(t_objects *objects, int cy_count)
{
	t_cylinder	*new_cylinders;
	int			i;

	new_cylinders = malloc(sizeof(t_cylinder) * (cy_count + 1));
	if (new_cylinders == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < cy_count)
	{
		new_cylinders[i] = objects->cylinders[i];
		++i;
	}
	if (cy_count != 0)
		free(objects->cylinders);
	objects->cylinders = new_cylinders;
	return (&new_cylinders[i]);
}
