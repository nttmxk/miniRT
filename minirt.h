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
# include "ft_math.h"

////////// testing
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
////////////////////////
typedef int t_object_type;
# define SP 0
# define LIGHT 1

typedef int t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
}	t_object;

typedef struct s_rec
{
	t_point	p;
	t_vec	n;
	double	tmin;
	double	tmax;
	double	t;
	int		front_face; // set_face_normal but ignore it for now
	t_color	albedo;
}	t_rec;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;
typedef struct s_scene
{
	t_rec		*rec;
	t_ray		*ray;
	t_object	*light;
	t_color		ambient;
}	t_scene;
typedef struct s_alight
{
	t_point	point;
	double	ratio;
}	t_alight;

typedef struct s_camera
{
	t_point	orig;
	t_vec	dir;
	t_point	left;
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

typedef struct s_scenes {
	t_ambient ambient;
	t_camera camera;
	t_light light;
	int mask;
} t_scenes;

typedef struct s_objects {
	t_sphere* spheres;
	t_plane* planes;
	t_cylinder* cylinders;
	int sp;
	int pl;
	int cy;
} t_objects;
// hakim added#

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

/*
 * parse.c
 */

void		parse_mini_rt(char* filename);

#endif