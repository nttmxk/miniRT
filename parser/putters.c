/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:42 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:43 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

void	put_color(char const *splitted, t_color *color)
{
	char	**rgb;

	rgb = ft_split(splitted, ',');
	check_length(rgb, 3);
	*color = make_color(ft_atoi(rgb[0])/255.0, ft_atoi(rgb[1])/255.0, ft_atoi(rgb[2])/255.0);
	color_check(*color);
	free(rgb);
}

void	put_coord(char const *splitted, t_point *point)
{
	char	**crd;

	crd = ft_split(splitted, ',');
	check_length(crd, 3);
	*point = make_point(ft_atod(crd[0]), ft_atod(crd[1]), ft_atod(crd[2]));
	free(crd);
}

void	put_normal_vec(char const *splitted, t_vec *vec)
{
	char	**dir;

	dir = ft_split(splitted, ',');
	check_length(dir, 3);
	*vec = make_vec(ft_atod(dir[0]), ft_atod(dir[1]), ft_atod(dir[2]));
	normalized_check(*vec);
	free(dir);
}
