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
#include "parser.h"

t_bool	check_length(char **splitted, int length)
{
	int	i;

	i = 0;
	while (splitted[i] != NULL)
		++i;
	if (i != length)
		error_msg_exit("wrong number of arguments\n");
	return (TRUE);
}

void	ratio_check(double ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		error_msg_exit("ratio must be in range [0.0,1.0]\n");
}

void	color_check(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_msg_exit("color must be in format R,G,B [0-255]\n");
}
