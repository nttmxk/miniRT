/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:27:13 by hakim             #+#    #+#             */
/*   Updated: 2022/08/08 18:27:14 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structures.h"
#include "ft_math.h"
#include "mlx.h"

static t_vec	cam_set_vup(t_vec dir)
{
	if (dir.x == 0 && dir.y != 0 && dir.z == 0)
		return (make_vec(0, dir.y, 1e-6));
	else
		return (make_vec(0, 1, 0));
}

void	camera_init(t_camera *camera)
{
	t_vec		w;
	t_vec		u;
	t_vec		v;

	camera->focal_len = tan((camera->fov * PI / 180.0) / 2.0);
	camera->viewport_h = camera->focal_len * 2;
	camera->viewport_w = camera->viewport_h * ((double)WIDTH / (double)HEIGHT);
	camera->dir = vunit(camera->dir);
	w = vunit(vsmul(camera->dir, -1));
	u = vunit(vcross(cam_set_vup(camera->dir), w));
	v = vcross(w, u);
	camera->horizontal = vsmul(u, camera->viewport_w);
	camera->vertical = vsmul(v, camera->viewport_h);
	camera->left = vminus(vminus(vminus(camera->orig,
					vdivide(camera->horizontal, 2)),
				vdivide(camera->vertical, 2)), w);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		exit(1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	if (!data->addr)
		exit(1);
}
