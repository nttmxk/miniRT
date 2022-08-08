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

static void	traverse_cy(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = 0;
	while (i < objects->pl)
	{
		dir = &objects->planes[i++].dir;
		if (xyz == 0)
			*dir = vunit(vplus(*dir, make_vec(change, 0, 0)));
		if (xyz == 1)
			*dir = vunit(vplus(*dir, make_vec(0, change, 0)));
		if (xyz == 2)
			*dir = vunit(vplus(*dir, make_vec(0, 0, change)));
	}
}

static void	traverse_pl(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = 0;
	while (i < objects->cy)
	{
		dir = &objects->cylinders[i++].dir;
		if (xyz == 0)
			*dir = vunit(vplus(*dir, make_vec(change, 0, 0)));
		if (xyz == 1)
			*dir = vunit(vplus(*dir, make_vec(0, change, 0)));
		if (xyz == 2)
			*dir = vunit(vplus(*dir, make_vec(0, 0, change)));
	}
}

static void	objs_rotate_keys(int key, t_data *data)
{
	if (key == 38)
		traverse_cy(&data->objects, 0, 0.1);
	if (key == 37)
		traverse_cy(&data->objects, 0, -0.1);
	if (key == 34)
		traverse_cy(&data->objects, 1, 0.1);
	if (key == 40)
		traverse_cy(&data->objects, 1, -0.1);
	if (key == 32)
		traverse_cy(&data->objects, 2, 0.1);
	if (key == 31)
		traverse_cy(&data->objects, 2, -0.1);
	if (key == 3)
		traverse_pl(&data->objects, 0, 0.1);
	if (key == 4)
		traverse_pl(&data->objects, 0, -0.1);
	if (key == 17)
		traverse_pl(&data->objects, 1, 0.1);
	if (key == 5)
		traverse_pl(&data->objects, 1, -0.1);
	if (key == 15)
		traverse_pl(&data->objects, 2, 0.1);
	if (key == 16)
		traverse_pl(&data->objects, 2, -0.1);
}

static void	camera_translate_keys(int key, t_data *data)
{
	t_vec	*orig;

	orig = &data->scene.camera.orig;
	if (key == 13)
		*orig = vplus(*orig, make_vec(0, 0.2, 0));
	if (key == 1)
		*orig = vplus(*orig, make_vec(0, -0.2, 0));
	if (key == 2)
		*orig = vplus(*orig, make_vec(0.2, 0, 0));
	if (key == 0)
		*orig = vplus(*orig, make_vec(-0.2, 0, 0));
	if (key == 12)
		*orig = vplus(*orig, make_vec(0, 0, 0.2));
	if (key == 14)
		*orig = vplus(*orig, make_vec(0, 0, -0.2));
}

int	press_key(int key, t_data *data)
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
	camera_translate_keys(key, data);
	objs_rotate_keys(key, data);
	draw(data);
	return (0);
}
