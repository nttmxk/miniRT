/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:40 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:41 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include "minirt.h"
#include "parser.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0' || s2[index] != '\0')
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

static size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

static void	parse_line(char *line, t_scene *scene, t_objects *objects)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split == NULL)
		error_msg_exit("malloc failure");
	if (ft_strcmp(split[0], "A") == 0 && check_length(split, 3))
		parse_ambient(split, scene);
	else if (ft_strcmp(split[0], "C") == 0 && check_length(split, 4))
		parse_camera(split, scene);
	else if (ft_strcmp(split[0], "L") == 0 && check_length(split, 4))
		parse_light(split, scene);
	else if (ft_strcmp(split[0], "sp") == 0 && check_length(split, 4))
		parse_sphere(split, objects);
	else if (ft_strcmp(split[0], "pl") == 0 && check_length(split, 4))
		parse_plane(split, objects);
	else if (ft_strcmp(split[0], "cy") == 0 && check_length(split, 6))
		parse_cylinder(split, objects);
	else
		error_msg_exit("Unknown file format\n");
	ft_free(split);
}

void	error_msg_exit(char *msg)
{
	printf("Error\n");
	printf("%s", msg);
	exit(1);
}

/*
 * if filename doesn't ends with .rt, return error;
 * if filename is empty, return error;
 * if filename is valid, read it line by line;
 */
void	parse_mini_rt(char *filename, t_data *data)
{
	int			rt;
	char		*line;

	if (filename == NULL)
		error_msg_exit("Invalid filename\n");
	if (ft_strcmp(filename + ft_strlen(filename) - 3, ".rt") != 0)
		error_msg_exit("Invalid filename extension\n");
	rt = open(filename, O_RDONLY);
	if (rt == -1)
	{
		printf("Error\nfile not found\n");
		return ;
	}
	line = get_next_line(rt);
	while (line != NULL)
	{
		if (line[0] != '\n')
			parse_line(line, &data->scene, &data->objects);
		free(line);
		line = get_next_line(rt);
	}
	free(line);
	if (!(data->scene.mask & 2))
		error_msg_exit("No camera\n");
	close(rt);
}
