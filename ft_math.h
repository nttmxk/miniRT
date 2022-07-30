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

typedef struct s_vec	t_point;
typedef struct s_vec	t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

double			s2_vec(t_vec vec);
double			len_vec(t_vec vec);
double			dot_vec(t_vec a, t_vec b);
t_vec			plus_vec(t_vec a, t_vec b);
t_vec			minus_vec(t_vec a, t_vec b);
t_vec			mul_vec(t_vec a, t_vec b);
t_vec			mul_vec_s(t_vec vec, double t);
t_vec			divide_vec_s(t_vec vec, double t);
t_vec			cross_vec(t_vec a, t_vec b);
t_vec			unit_vec(t_vec vec);

#endif
