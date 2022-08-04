/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:23:09 by jinoh             #+#    #+#             */
/*   Updated: 2022/07/30 15:23:11 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
//# include "mlx.h"
//# include "ft_math.h"
# include "structures.h"

////////// testing
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
////////////////////////

/*
 * 	ft_constructor.c
 */
t_vec		make_vec(double x, double y, double z);
t_point		make_point(double x, double y, double z);
t_color		make_color(double x, double y, double z);
t_ray		make_ray(t_point p, t_vec vec);
t_ray		make_view(t_camera *cam, double u, double v);

/*
 * 	test.c
 */
t_point		ray_at(t_ray *ray, double t);
t_camera	make_cam(void);
void		print_vec(t_vec vec);
int			hit_sphere(t_sphere *sp, t_ray *ray, t_rec *rec);
int			color_sphere(t_sphere *sp, t_ray *ray);
int			lighting(t_scene *scene);
t_color		point_light_get(t_scene *scene, t_light *light);
t_vec		reflect(t_vec v, t_vec n);

/*
 * parse.c
 */

void		parse_mini_rt(char* filename);

#endif
