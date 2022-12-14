/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:05 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:14 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

/* parse_scenes */
void		parse_ambient(char **splitted, t_scene *scene);
void		parse_camera(char **splitted, t_scene *scene);
void		parse_light(char **splitted, t_scene *scene);

/* parse_objs */
void		parse_sphere(char **splitted, t_objects *objects);
void		parse_plane(char **splitted, t_objects *objects);
void		parse_cylinder(char **splitted, t_objects *objects);

/* validator */
void		fov_check(double fov);
void		dia_check(double dia);
t_bool		check_length(char **splitted, int length);
void		ratio_check(double ratio);
void		color_check(int r, int g, int b);
void		normalized_check(t_vec normal);

/* putters */
void		put_color(char const *splitted, t_color *color);
void		put_coord(char const *splitted, t_point *point);
void		put_normal_vec(char const *splitted, t_vec *vec);

/* reallocs */
t_sphere	*realloc_sp(t_objects *objects, int sp_count);
t_plane		*realloc_pl(t_objects *objects, int pl_count);
t_cylinder	*realloc_cy(t_objects *objects, int cy_count);

/* utils */
char		**ft_split(char const *s, char c);
void		ft_free(char **big);
double		ft_atod(const char *str);
int			ft_atoi(const char *str);
void		error_msg_exit(char *msg);

#endif
