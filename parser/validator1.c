/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:45 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:46 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	check_length(char **splitted, int length)
{
	int	i;

	i = 0;
	while (splitted[i] != NULL)
		++i;
	if (i != length)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	return (TRUE);
}

void	ratio_check(double ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
	{
		printf("ambient ratio must be in range [0.0,1.0]\n");
		exit(1);
	}
}

void	color_check(t_color color)
{
	double	r;
	double	g;
	double	b;

	r = color.x;
	g = color.y;
	b = color.z;
	if (r < 0.0 || r > 255.0 || g < 0.0 || g > 255.0 || b < 0.0 || b > 255.0)
	{
		printf("Ambient color must be in format R,G,B\n");
		exit(1);
	}
}
