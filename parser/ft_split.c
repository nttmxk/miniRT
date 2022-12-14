/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:45:39 by hakim             #+#    #+#             */
/*   Updated: 2021/11/11 22:38:41 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	wordcount(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while ((s[i] == c || s[i] == '\t') && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != '\0' && s[i] != c && s[i] != '\t')
			i++;
		while ((s[i] == c || s[i] == '\t') && s[i] != '\0')
			i++;
	}	
	return (count);
}

static void	get_si(int *size, int *i, char const *s, char c)
{
	while (s[*i] != '\0' && (s[*i] == c || s[*i] == '\t'))
		*i += 1;
	while (s[*i] != '\0' && s[*i] != c && s[*i] != '\t')
	{
		*size += 1;
		*i += 1;
	}
}

void	ft_free(char **big)
{
	int	index;

	index = 0;
	while (big[index] != NULL)
	{
		free(big[index]);
		big[index] = NULL;
		++index;
	}
	free(big);
}

static void	go_split(char **big, char const *s, char c, int bigdex)
{
	int	i;
	int	size;
	int	sindex;

	i = 0;
	while (s[i] != '\0')
	{
		size = 0;
		get_si(&size, &i, s, c);
		if (size == 0)
			continue ;
		big[bigdex] = (char *)malloc(sizeof(char) * (size + 1));
		if (big[bigdex] == 0)
		{
			ft_free(big);
			return ;
		}
		sindex = 0;
		i -= size;
		while (sindex < size)
			big[bigdex][sindex++] = s[i++];
		big[bigdex][sindex] = '\0';
		++bigdex;
	}
	big[bigdex] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**big;
	int		size;
	int		bigdex;

	if (s == 0)
		return (0);
	size = wordcount(s, c);
	big = (char **)malloc(sizeof(char *) * (size + 1));
	if (big == 0)
		return (0);
	bigdex = 0;
	go_split(big, s, c, bigdex);
	return (big);
}	
