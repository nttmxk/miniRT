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
# include <mlx.h>
# include <math.h>
# include "ft_math.h"

////////// testing
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# define ITER_MAX	100
# define A			0
# define D			2
# define F			3
# define C			8
# define LEFT		123
# define RIGHT		124
# define DOWN		125
# define UP			126
# define PLUS        24
# define MINUS       27
# define ZOOM_IN     5
# define ZOOM_OUT	4
//////////
typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;
///////// in subject
typedef struct s_alight
{
	t_point	point;
	double	ratio;
}	t_alight;

typedef struct s_camera
{
	t_point	orig;
	t_vec	dir;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_point	point;
	double	bright;
	t_color	color; // unused in mandatory part
}	t_light;

typedef struct s_sphere
{
	t_point	point;
	double	dia;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_point	point;
	t_vec	dir;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_point	point;
	t_vec	dir;
	double	dia;
	double	height;
	t_color	color;
}	t_cylinder;
////////////
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		type;
	int		x;
	int		y;
	int		press_f;
	int		color;
	int		bpp;
	int		line_length;
	int		endian;
	double	a;
	double	b;
	double	zoom_rate;
}	t_data;

/*
 * 	ft_constructor.c
 */
t_vec	make_vec(double x, double y, double z);
t_point	make_point(double x, double y, double z);
t_color	make_color(double x, double y, double z);
t_ray	make_ray(t_point p, t_vec vec);

#endif
