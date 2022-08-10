/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:34 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:37 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 * x,y,z coordinates of the sphere center: 0.0,0.0,20.6
 ∗ the sphere diameter: 12.6
 ∗ R,G,B colors in range [0-255]: 10, 0, 255
 */
void	parse_sphere(char **splitted, t_objects *objects)
{
	t_sphere	*sphere;

	sphere = realloc_sp(objects, objects->sp);
	objects->sp++;
	put_coord(splitted[1], &sphere->point);
	sphere->dia = ft_atod(splitted[2]);
	dia_check(sphere->dia);
	put_color(splitted[3], &sphere->color);
}

/*
 * x,y,z coordinates: 0.0,0.0,-10.0
 * 3d normalized orientation vector.
 * In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
 * R,G,B colors in range [0-255]: 0, 0, 255
 */
void	parse_plane(char **splitted, t_objects *objects)
{
	t_plane	*plane;

	plane = realloc_pl(objects, objects->pl);
	objects->pl++;
	put_coord(splitted[1], &plane->point);
	put_normal_vec(splitted[2], &plane->dir);
	put_color(splitted[3], &plane->color);
}

/*
 * x,y,z coordinates: 50.0,0.0,20.6
 ∗ 3d normalized orientation vector.
 In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
 ∗ the cylinder diameter: 14.2
 ∗ the cylinder height: 21.42
 ∗ R,G,B colors in range [0,255]: 10, 0, 255
 */
void	parse_cylinder(char **splitted, t_objects *objects)
{
	t_cylinder	*cylinder;

	cylinder = realloc_cy(objects, objects->cy);
	objects->cy++;
	put_coord(splitted[1], &cylinder->point);
	put_normal_vec(splitted[2], &cylinder->dir);
	cylinder->dia = ft_atod(splitted[3]);
	dia_check(cylinder->dia);
	cylinder->height = ft_atod(splitted[4]);
	dia_check(cylinder->height);
	put_color(splitted[5], &cylinder->color);
}
