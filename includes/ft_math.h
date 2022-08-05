/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:23:25 by jinoh             #+#    #+#             */
/*   Updated: 2022/07/30 15:23:26 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <math.h>
# include "structures.h"
# define SKYBLUE 0x00ccff

double			s2_vec(t_vec vec);
double			vlen(t_vec vec);
double			vdot(t_vec a, t_vec b);
t_vec			vplus(t_vec a, t_vec b);
t_vec			vminus(t_vec a, t_vec b);
t_vec			vmul(t_vec a, t_vec b);
t_vec			vsmul(t_vec vec, double t);
t_vec			vdivide(t_vec vec, double t);
t_vec			vcross(t_vec a, t_vec b);
t_vec			vunit(t_vec vec);
t_vec			vmin(t_vec a, t_vec b);

int				get_color(t_color c);

#endif
