#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

/* parse_scenes */
void		parse_ambient(char **splitted, t_scenes *scene);
void		parse_camera(char **splitted, t_scenes *scene);
void		parse_light(char **splitted, t_scenes *scene);

/* parse_objs */
void		parse_sphere(char **splitted, t_objects *objects);
void		parse_plane(char **splitted, t_objects *objects);
void		parse_cylinder(char **splitted, t_objects *objects);


/* validator */
void		fov_check(double fov);
void		dia_check(double dia);
t_bool		check_splitted_length(char **splitted, int length);
void		ratio_check(double ratio);
void		color_check(t_color color);
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
double		ft_atod(const char *str);
int			ft_atoi(const char *str);

#endif