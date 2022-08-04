#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line/get_next_line.h"
#include "minirt.h"
#include <string.h> // string and strcmp should be ft_implemented

char	**ft_split(char const *s, char c);
double ft_atod(const char *str);
int ft_atoi(const char *str);
//정규벡터 길이 검사

t_sphere* realloc_sp(t_objects *objects, int sp_count) {
	t_sphere *new_spheres;
	int i;

	new_spheres = malloc(sizeof(t_sphere) * (sp_count + 1));
	if (new_spheres == NULL) {
		printf("Error: malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < sp_count) {
		new_spheres[i] = objects->spheres[i];
		++i;
	}
	if (sp_count != 0)
		free(objects->spheres);
	objects->spheres = new_spheres;
	return (&new_spheres[i]);
}

t_plane* realloc_pl(t_objects *objects, int pl_count) {
	t_plane *new_planes;
	int i;

	new_planes = malloc(sizeof(t_plane) * (pl_count + 1));
	if (new_planes == NULL) {
		printf("Error: malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < pl_count) {
		new_planes[i] = objects->planes[i];
		++i;
	}
	if (pl_count != 0)
		free(objects->planes);
	objects->planes = new_planes;
	return (&new_planes[i]);
}

t_cylinder* realloc_cy(t_objects *objects, int cy_count) {
	t_cylinder *new_cylinders;
	int i;

	new_cylinders = malloc(sizeof(t_cylinder) * (cy_count + 1));
	if (new_cylinders == NULL) {
		printf("Error: malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < cy_count) {
		new_cylinders[i] = objects->cylinders[i];
		++i;
	}
	if (cy_count != 0)
		free(objects->cylinders);
	objects->cylinders = new_cylinders;
	return (&new_cylinders[i]);
}

t_bool check_splitted_length(char **splitted, int length) {
	int i;

	i = 0;
	while (splitted[i] != NULL) {
		++i;
	}
	if (i != length) {
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	return (TRUE);
}

t_bool in_range(double value, double min, double max) {
	if (value <= min || value >= max) {
		return (FALSE);
	}
	return (TRUE);
}

void ratio_check(double ratio) {
	if (ratio < 0.0 || ratio > 1.0) {
		printf("ambient ratio must be in range [0.0,1.0]\n");
		exit(1);
	}
}

void color_check(t_color color) {
	double r = color.x;
	double g = color.y;
	double b = color.z;

	if (r < 0.0 || r > 255.0 || g < 0.0 || g > 255.0 || b < 0.0 || b > 255.0) {
		printf("Ambient color must be in format R,G,B\n");
		exit(1);
	}
}

void normalized_check(t_vec normal) {
//	if (!in_range(normal.x, -1.0, 1.0) || !in_range(normal.y, -1.0, 1.0) || !in_range(normal.z, -1.0, 1.0)) {
//		printf("Error: normal vector is not normalized\n");
//		exit(1);
//	}
	//normalvector인지 확인
}

void dia_check(double dia) {
	if (dia <= 0.0) {
		printf("Error: sphere diameter must be greater than zero\n");
		exit(1);
	}
}

void put_color(char const *splitted, t_color *color)
{
	char** rgb_chunk = ft_split(splitted, ',');
	check_splitted_length(rgb_chunk, 3);
	*color = make_color(ft_atoi(rgb_chunk[0]), ft_atoi(rgb_chunk[1]), ft_atoi(rgb_chunk[2]));
	color_check(*color);
	free(rgb_chunk);
}

void put_coord(char const *splitted, t_point *point)
{
	char **coord = ft_split(splitted, ',');
	check_splitted_length(coord, 3);
	*point = make_point(ft_atod(coord[0]), ft_atod(coord[1]), ft_atod(coord[2]));
	free(coord);
}

void put_normal_vec(char const *splitted, t_vec *vec)
{
	char **dir = ft_split(splitted, ',');
	check_splitted_length(dir, 3);
	*vec = make_vec(ft_atod(dir[0]), ft_atod(dir[1]), ft_atod(dir[2]));
	normalized_check(*vec);
	free(dir);
}

void parse_ambient(char **splitted, t_scenes *scene) {
// ambient lighting ratio in range [0.0,1.0]: 0.2 // R,G,B colors in range [0-255]: 255, 255, 255
	t_ambient *ambient;

	ambient = &scene->ambient;
	ambient->ratio = ft_atod(splitted[1]);
	ratio_check(ambient->ratio);
	put_color(splitted[2], &ambient->color);
	if (scene->mask & 1) {
		printf("Error: ambient already defined\n");
		exit(1);
	}
	scene->mask += 1;
}

void check_fov(double fov) {
	if (!in_range(fov, 0.0, 180.0)) {
		printf("Error: fov must be in range [0.0,180.0]\n");
		exit(1);
	}
}

void parse_camera(char **splitted, t_scenes *scene) {
//∗ x,y,z coordinates of the view point: 0.0,0.0,20.6
//∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
//∗ FOV : Horizontal field of view in degrees in range [0,180]
	t_camera *camera = &scene->camera;

	put_coord(splitted[1], &camera->orig);
	put_normal_vec(splitted[2], &camera->dir);
	camera->fov = ft_atod(splitted[3]);
	check_fov(camera->fov);
	if (scene->mask & 2) {
		printf("Error: camera already defined\n");
		exit(1);
	}
	scene->mask = 2;
}

void parse_light(char **splitted, t_scenes *scene) {
//∗ x,y,z coordinates of the light point: 0.0,0.0,20.6
//∗ the light brightness ratio in range [0.0,1.0]: 0.6
//∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
	t_light *light = &scene->light;

	put_coord(splitted[1], &light->point);
	light->bright = ft_atod(splitted[2]);
	ratio_check(light->bright);
	put_color(splitted[3], &light->color);
	if (scene->mask & 4) {
		printf("Error: light already defined\n");
		exit(1);
	}
	scene->mask = 4;
}

void parse_sphere(char **splitted, t_objects *objects) {
//∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
//∗ the sphere diameter: 12.6
//∗ R,G,B colors in range [0-255]: 10, 0, 255
	t_sphere *sphere = realloc_sp(objects, objects->sp);
	objects->sp++;
	put_coord(splitted[1], &sphere->point);
	sphere->dia = ft_atod(splitted[2]);
	dia_check(sphere->dia);
	put_color(splitted[3], &sphere->color);
}

void parse_plane(char **splitted, t_objects *objects) {
//∗ x,y,z coordinates: 0.0,0.0,-10.0
//∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
//∗ R,G,B colors in range [0-255]: 0, 0, 255
	t_plane *plane = realloc_pl(objects, objects->pl);
	objects->pl++;
	put_coord(splitted[1], &plane->point);
	put_normal_vec(splitted[2], &plane->dir);
	put_color(splitted[3], &plane->color);
}

void parse_cylinder(char **splitted, t_objects *objects) {
//∗ x,y,z coordinates: 50.0,0.0,20.6
//∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
//∗ the cylinder diameter: 14.2
//∗ the cylinder height: 21.42
//∗ R,G,B colors in range [0,255]: 10, 0, 255
	t_cylinder *cylinder = realloc_cy(objects, objects->cy);
	objects->cy++;
	put_coord(splitted[1], &cylinder->point);
	put_normal_vec(splitted[2], &cylinder->dir);
	cylinder->dia = ft_atod(splitted[3]);
	dia_check(cylinder->dia);
	cylinder->height = ft_atod(splitted[4]);
	dia_check(cylinder->height);
	put_color(splitted[5], &cylinder->color);
}

void parse_line(char *line, t_scenes* scene, t_objects *objects) {
	char **splitted = ft_split(line, ' ');
	if (splitted == NULL) {
		return ;
	}
	//A,C,L can only be used once in the scene file.
	if (strcmp(splitted[0], "A") == 0 && check_splitted_length(splitted, 3)) {
		parse_ambient(splitted, scene);
	} else if (strcmp(splitted[0], "C") == 0 && check_splitted_length(splitted, 4)) {
		parse_camera(splitted, scene);
	} else if (strcmp(splitted[0], "L") == 0 && check_splitted_length(splitted, 4)) {
		parse_light(splitted, scene);
	} else if (strcmp(splitted[0], "sp") == 0 && check_splitted_length(splitted, 4)) {
		parse_sphere(splitted, objects);
	} else if (strcmp(splitted[0], "pl") == 0 && check_splitted_length(splitted, 4)) {
		parse_plane(splitted, objects);
	} else if (strcmp(splitted[0], "cy") == 0 && check_splitted_length(splitted, 6)) {
		parse_cylinder(splitted, objects);
	} else {
		printf("Error: unknown format\n");
		exit(1);
	}
	free(splitted);
}

void parse_mini_rt(char* filename) {
	//if filename doesn't ends with .rt, return error;
	//if filename is empty, return error;
	//if filename is valid, read it line by line;
	t_scenes scene = {0};
	t_objects objects = {0};
	int rt = open(filename, O_RDONLY);

	if (rt == -1) {
		printf("Error: file not found\n");
		return;
	}

	char* line = NULL;
	line = get_next_line(rt);
	while (line != NULL) {
		//if line consists of a line break only, skip it;
		if (line[0] != '\n')
			parse_line(line, &scene, &objects);
		free(line);
		line = get_next_line(rt);
	}
	free(line);
	close(rt);
}

//int main(int ac, char **av)
//{
//	if (ac != 2)
//		return 1; // error
//	mini_rt(av[1]);
//	return 0;
//}