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

static int	check_space(const char *str)
{
	int	index;

	index = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	return (index);
}

int	ft_atoi(const char *str, int *ret)
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
	if (str[index] == '\0')
		exit(1);
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (str[index] != '\0' && str[index] != '\n')
		exit(1);
	if (result > 9223372036854775807 && plma == 1)
		return (0);
	else if (result > 9223372036854775808ULL && plma == -1)
		return (-1);
	return ((int)result * plma);
}

double ft_atod(const char *str)
{
	double	result;
	double	plma;
	int		index;
	int		dot;
	int		i;

	index = check_space(str);
	plma = 1;
	if (str[index] == '-')
		plma = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	if (str[index] == '\0')
		exit(1);
	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (str[index] == '.')
	{
		if (str[index] == '\0' || str[index] == '\n')
			exit(1);
		dot = 1;
		index++;
		while (str[index] >= '0' && str[index] <= '9')
		{
			dot *= 10;
			result = result + (double)(str[index] - '0') / dot;
			index++;
		}
	}
	if (str[index] != '\0' && str[index] != '\n')
		exit(1);
	return (result * plma);
}