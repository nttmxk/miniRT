/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 05:32:07 by hakim             #+#    #+#             */
/*   Updated: 2022/08/05 05:32:11 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef int				t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_vec	t_point;
typedef struct s_vec	t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

/* front_face -> set_face_normal but ignore it for now */
typedef struct s_rec
{
	t_point	p;
	t_vec	n;
	double	tmin;
	double	tmax;
	double	t;
	int		front_face;
	t_color	albedo;
}	t_rec;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	orig;
	t_vec	dir;
	t_point	left;
	double	fov;
}	t_camera;

/* color is unused in mandatory part */
typedef struct s_light
{
	t_point	point;
	double	bright;
	t_color	color;
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

// hakim added
typedef struct s_ambient
{
	t_color	color;
	double	ratio;
}	t_ambient;

typedef struct s_scene {
	t_rec		rec;
	t_ray		ray;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	int			mask;
}	t_scene;

typedef struct s_objects {
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			sp;
	int			pl;
	int			cy;
}	t_objects;
// hakim added#

#endif
