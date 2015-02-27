/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 10:28:21 by gmp               #+#    #+#             */
/*   Updated: 2015/02/27 12:48:52 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# define WIDTH 800
# define HEIGTH 600

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

/* STRUCTURES */

typedef struct 		s_point
{
	int 			x;
	int 			y;
	int 			z;
}					t_point;

typedef struct 		s_color
{
	int 			r;
	int 			g;
	int 			b;
}					t_color;

typedef struct 		s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int 	bpp;
	int 	size_line;
	int 	endian;
	int 	color;
	int 	scale;
	void (*tab[42])();
}					t_env;

/* PROTOTYPES */

int 	expose_hook(t_env *e);
int 	key_hook(int keycode, t_env *e);
void 	clearImg(t_env *e);
void	initPtrTab(t_env *e);
t_env	*getEnv();
int 	keyMap(int keycode);
int 	img_pixel_put(t_env *e, int x, int y, int color);
void 	draw_line_mlx(t_env *e, t_point a, t_point b);

void	drawGradient(t_env *e);


/* KEY FUNCTION */

void	key_escape(void);
void 	key_arrow_up(void);
void 	key_arrow_down(void);
void 	key_arrow_right(void);
void 	key_arrow_left(void);
void 	key_p(void);
void 	key_m(void);
void 	key_1(void);
void 	key_2(void);

/* END PROTOTYPES */

#endif