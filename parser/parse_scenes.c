/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:38 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:40 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdlib.h"
#include "stdio.h"

/*
 * ambient lighting ratio in range [0.0,1.0]: 0.2
 * R,G,B colors in range [0-255]: 255, 255, 255
 */
void	parse_ambient(char **splitted, t_scene *scene)
{
	t_ambient	*ambient;

	ambient = &scene->ambient;
	ambient->ratio = ft_atod(splitted[1]);
	ratio_check(ambient->ratio);
	put_color(splitted[2], &ambient->color);
	if (scene->mask & 1)
		error_msg_exit("ambient already defined\n");
	scene->mask += 1;
}

/*
 * x,y,z coordinates of the view point: 0.0,0.0,20.6
 ∗ 3d normalized orientation vector.
 * In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
 ∗ FOV : Horizontal field of view in degrees in range [0,180]
 */
void	parse_camera(char **splitted, t_scene *scene)
{
	t_camera	*camera;

	camera = &scene->camera;
	put_coord(splitted[1], &camera->orig);
	put_normal_vec(splitted[2], &camera->dir);
	camera->fov = ft_atod(splitted[3]);
	fov_check(camera->fov);
	if (scene->mask & 2)
		error_msg_exit("camera already defined\n");
	scene->mask = 2;
}

/*
 * x,y,z coordinates of the light point: 0.0,0.0,20.6
 ∗ the light brightness ratio in range [0.0,1.0]: 0.6
 ∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
 */
void	parse_light(char **splitted, t_scene *scene)
{
	t_light	*light;

	light = &scene->light;
	put_coord(splitted[1], &light->point);
	light->bright = ft_atod(splitted[2]);
	ratio_check(light->bright);
	put_color(splitted[3], &light->color);
	if (scene->mask & 4)
		error_msg_exit("light already defined\n");
	scene->mask = 4;
}
