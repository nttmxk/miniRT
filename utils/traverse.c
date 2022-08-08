/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 01:50:45 by hakim             #+#    #+#             */
/*   Updated: 2022/08/09 01:50:47 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_math.h"

void	traverse_pl_rotate(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = -1;
	while (++i < objects->pl)
	{
		dir = &objects->planes[i].dir;
		if (xyz == 0)
			*dir = vunit(vplus(*dir, make_vec(change, 0, 0)));
		if (xyz == 1)
			*dir = vunit(vplus(*dir, make_vec(0, change, 0)));
		if (xyz == 2)
			*dir = vunit(vplus(*dir, make_vec(0, 0, change)));
	}
}

void	traverse_pl_translate(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = -1;
	while (++i < objects->pl)
	{
		dir = &objects->planes[i].point;
		if (xyz == 0)
			*dir = vplus(*dir, make_vec(change, 0, 0));
		if (xyz == 1)
			*dir = vplus(*dir, make_vec(0, change, 0));
		if (xyz == 2)
			*dir = vplus(*dir, make_vec(0, 0, change));
	}
}

void	traverse_cy_rotate(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = -1;
	while (++i < objects->cy)
	{
		dir = &objects->cylinders[i].dir;
		if (xyz == 0)
			*dir = vunit(vplus(*dir, make_vec(change, 0, 0)));
		if (xyz == 1)
			*dir = vunit(vplus(*dir, make_vec(0, change, 0)));
		if (xyz == 2)
			*dir = vunit(vplus(*dir, make_vec(0, 0, change)));
	}
}

void	traverse_cy_translate(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = -1;
	while (++i < objects->cy)
	{
		dir = &objects->cylinders[i].point;
		if (xyz == 0)
			*dir = vplus(*dir, make_vec(change, 0, 0));
		if (xyz == 1)
			*dir = vplus(*dir, make_vec(0, change, 0));
		if (xyz == 2)
			*dir = vplus(*dir, make_vec(0, 0, change));
	}
}

void	traverse_sp_translate(t_objects *objects, int xyz, double change)
{
	int		i;
	t_vec	*dir;

	i = -1;
	while (++i < objects->sp)
	{
		dir = &objects->spheres[i].point;
		if (xyz == 0)
			*dir = vplus(*dir, make_vec(change, 0, 0));
		if (xyz == 1)
			*dir = vplus(*dir, make_vec(0, change, 0));
		if (xyz == 2)
			*dir = vplus(*dir, make_vec(0, 0, change));
	}
}
