/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:56:20 by hakim             #+#    #+#             */
/*   Updated: 2021/11/14 12:22:17 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

static void	if_end_exit(char c, char end)
{
	if (end == 'y')
	{
		if (c == '\0' || c == '\n')
			error_msg_exit("non numeric value detected\n");
	}
	if (end == 'n')
	{
		if (c != '\0' && c != '\n')
			error_msg_exit("non numeric value detected\n");
	}
}

static int	check_space(const char *str)
{
	int	index;

	index = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	return (index);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					plma;
	int					index;

	index = check_space(str);
	plma = 1;
	if (str[index] == '-')
		plma = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	result = 0;
	if_end_exit(str[index], 'y');
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if_end_exit(str[index], 'n');
	if (result > 9223372036854775807 && plma == 1)
		return (0);
	else if (result > 9223372036854775808ULL && plma == -1)
		return (-1);
	return ((int)result * plma);
}

static void	under_the_dot(const char *str, double *result, int *index)
{
	int	dot;

	if (str[(*index)] == '.')
	{
		if_end_exit(str[(*index)], 'y');
		dot = 1;
		(*index)++;
		while (str[(*index)] >= '0' && str[(*index)] <= '9')
		{
			dot *= 10;
			(*result) = (*result) + (double)(str[(*index)] - '0') / dot;
			(*index)++;
		}
	}
}

double	ft_atod(const char *str)
{
	double	result;
	double	plma;
	int		index;

	index = check_space(str);
	plma = 1;
	if (str[index] == '-')
		plma = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	if_end_exit(str[index], 'y');
	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	under_the_dot(str, &result, &index);
	if_end_exit(str[index], 'n');
	return (result * plma);
}
