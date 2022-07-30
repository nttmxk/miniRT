#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define	WIN_WIDTH	800
# define	WIN_HEIGHT	600
# define	ITER_MAX	100
# define	A			0
# define	D			2
# define	F			3
# define	C			8
# define	LEFT		123
# define	RIGHT		124
# define	DOWN		125
# define	UP			126
# define	PLUS        24
# define	MINUS       27
# define	ZOOM_IN     5
# define	ZOOM_OUT	4

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

#endif
