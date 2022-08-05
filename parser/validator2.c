/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:47 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:49 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	in_range(double value, double min, double max)
{
	if (value <= min || value >= max)
		return (FALSE);
	return (TRUE);
}

void	dia_check(double dia)
{
	if (dia <= 0.0)
	{
		printf("Error: sphere diameter must be greater than zero\n");
		exit(1);
	}
}

void	fov_check(double fov)
{
	if (!in_range(fov, 0.0, 180.0))
	{
		printf("Error: fov must be in range [0.0,180.0]\n");
		exit(1);
	}
}

/* normalvector인지 확인해야함 */
void	normalized_check(t_vec normal)
{
	if (!in_range(normal.x, -1.0, 1.0)
		|| !in_range(normal.y, -1.0, 1.0)
		|| !in_range(normal.z, -1.0, 1.0))
	{
		printf("Error: normal vector is not normalized\n");
		exit(1);
	}
}
