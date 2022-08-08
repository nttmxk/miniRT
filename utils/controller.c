/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 00:21:56 by hakim             #+#    #+#             */
/*   Updated: 2022/08/09 00:21:57 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_math.h"

void	camera_translate_keys(int key, t_data *data)
{
	t_vec	*orig;

	orig = &data->scene.camera.orig;
	if (key == 19)
		*orig = vplus(*orig, make_vec(0, 0.2, 0));
	if (key == 13)
		*orig = vplus(*orig, make_vec(0, -0.2, 0));
	if (key == 14)
		*orig = vplus(*orig, make_vec(0.2, 0, 0));
	if (key == 12)
		*orig = vplus(*orig, make_vec(-0.2, 0, 0));
	if (key == 18)
		*orig = vplus(*orig, make_vec(0, 0, 0.2));
	if (key == 20)
		*orig = vplus(*orig, make_vec(0, 0, -0.2));
	if (key == 30)
		traverse_sp_translate(&data->objects, 0, 0.2);
	if (key == 35)
		traverse_sp_translate(&data->objects, 0, -0.2);
	if (key == 27)
		traverse_sp_translate(&data->objects, 1, 0.2);
	if (key == 33)
		traverse_sp_translate(&data->objects, 1, -0.2);
}

void	camera_rotate_keys(int key, t_data *data)
{
	t_vec	*dir;

	dir = &data->scene.camera.dir;
	if (key == 53)
		exit(0);
	if (key == 126)
		*dir = vunit(vplus(*dir, make_vec(0, 0.1, 0)));
	if (key == 125)
		*dir = vunit(vplus(*dir, make_vec(0, -0.1, 0)));
	if (key == 124)
		*dir = vunit(vplus(*dir, make_vec(0.1, 0, 0)));
	if (key == 123)
		*dir = vunit(vplus(*dir, make_vec(-0.1, 0, 0)));
	if (key == 29)
		traverse_sp_translate(&data->objects, 2, 0.2);
	if (key == 24)
		traverse_sp_translate(&data->objects, 2, -0.2);
}

void	light_translate_keys(int key, t_data *data)
{
	t_vec	*orig;

	orig = &data->scene.light.point;
	if (key == 1)
		*orig = vplus(*orig, make_vec(0, 0.2, 0));
	if (key == 7)
		*orig = vplus(*orig, make_vec(0, -0.2, 0));
	if (key == 8)
		*orig = vplus(*orig, make_vec(0.2, 0, 0));
	if (key == 6)
		*orig = vplus(*orig, make_vec(-0.2, 0, 0));
	if (key == 0)
		*orig = vplus(*orig, make_vec(0, 0, 0.2));
	if (key == 2)
		*orig = vplus(*orig, make_vec(0, 0, -0.2));
}

void	objs_rotate_keys(int key, t_data *data)
{
	if (key == 32)
		traverse_cy_rotate(&data->objects, 0, 0.1);
	if (key == 31)
		traverse_cy_rotate(&data->objects, 0, -0.1);
	if (key == 28)
		traverse_cy_rotate(&data->objects, 1, 0.1);
	if (key == 34)
		traverse_cy_rotate(&data->objects, 1, -0.1);
	if (key == 26)
		traverse_cy_rotate(&data->objects, 2, 0.1);
	if (key == 25)
		traverse_cy_rotate(&data->objects, 2, -0.1);
	if (key == 15)
		traverse_pl_rotate(&data->objects, 0, 0.1);
	if (key == 16)
		traverse_pl_rotate(&data->objects, 0, -0.1);
	if (key == 23)
		traverse_pl_rotate(&data->objects, 1, 0.1);
	if (key == 17)
		traverse_pl_rotate(&data->objects, 1, -0.1);
	if (key == 21)
		traverse_pl_rotate(&data->objects, 2, 0.1);
	if (key == 22)
		traverse_pl_rotate(&data->objects, 2, -0.1);
}

void	objs_translate_keys(int key, t_data *data)
{
	if (key == 9)
		traverse_cy_translate(&data->objects, 0, 0.2);
	if (key == 45)
		traverse_cy_translate(&data->objects, 0, -0.2);
	if (key == 5)
		traverse_cy_translate(&data->objects, 1, 0.2);
	if (key == 11)
		traverse_cy_translate(&data->objects, 1, -0.2);
	if (key == 3)
		traverse_cy_translate(&data->objects, 2, 0.2);
	if (key == 4)
		traverse_cy_translate(&data->objects, 2, -0.2);
	if (key == 46)
		traverse_pl_translate(&data->objects, 0, 0.2);
	if (key == 47)
		traverse_pl_translate(&data->objects, 0, -0.2);
	if (key == 37)
		traverse_pl_translate(&data->objects, 1, 0.2);
	if (key == 47)
		traverse_pl_translate(&data->objects, 1, -0.2);
	if (key == 40)
		traverse_pl_translate(&data->objects, 2, 0.2);
	if (key == 39)
		traverse_pl_translate(&data->objects, 2, -0.2);
}
