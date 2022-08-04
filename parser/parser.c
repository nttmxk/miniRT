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
#include <string.h> // string and strcmp should be ft_implemented
#include "parser.h"

/* 정규벡터 길이 검사 */
void	parse_line(char *line, t_scenes *scene, t_objects *objects)
{
	char	**splitted;

	splitted = ft_split(line, ' ');
	if (splitted == NULL)
		return ;
	if (strcmp(splitted[0], "A") == 0 && check_length(splitted, 3))
		parse_ambient(splitted, scene);
	else if (strcmp(splitted[0], "C") == 0 && check_length(splitted, 4))
		parse_camera(splitted, scene);
	else if (strcmp(splitted[0], "L") == 0 && check_length(splitted, 4))
		parse_light(splitted, scene);
	else if (strcmp(splitted[0], "sp") == 0 && check_length(splitted, 4))
		parse_sphere(splitted, objects);
	else if (strcmp(splitted[0], "pl") == 0 && check_length(splitted, 4))
		parse_plane(splitted, objects);
	else if (strcmp(splitted[0], "cy") == 0 && check_length(splitted, 6))
		parse_cylinder(splitted, objects);
	else
	{
		printf("Error: unknown format\n");
		exit(1);
	}
	free(splitted);
}

/*
 * if filename doesn't ends with .rt, return error;
 * if filename is empty, return error;
 * if filename is valid, read it line by line;
 */
void	parse_mini_rt(char *filename)
{
	t_scenes	scene;
	t_objects	objects;
	int			rt;
	char		*line;

	rt = open(filename, O_RDONLY);
	if (rt == -1)
	{
		printf("Error: file not found\n");
		return ;
	}
	line = get_next_line(rt);
	while (line != NULL)
	{
		if (line[0] != '\n')
			parse_line(line, &scene, &objects);
		free(line);
		line = get_next_line(rt);
	}
	free(line);
	close(rt);
}

/*int main(int ac, char **av)
{
	if (ac != 2)
		return 1; // error
	mini_rt(av[1]);
	return 0;
}*/
