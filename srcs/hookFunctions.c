/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookFunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 12:47:30 by gmp               #+#    #+#             */
/*   Updated: 2015/02/25 18:04:09 by gmp              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

int 	key_hook(int keycode, t_env *e)
{
	if (ft_isprint(keycode) == 1)
		ft_putnbr(keycode);
	else
		ft_putnbr(keycode);
	ft_putchar('\n');
	if (keyMap(keycode) != -1)
		e->tab[keyMap(keycode)]();
	return (0);
}

int		img_pixel_put(t_env *e, int x, int y, int color)
{
	unsigned int	new_color;
	int	i;

	if (x >= WIDTH || y >= HEIGTH || x < 0 || y < 0)
		return -1;
	new_color = mlx_get_color_value(e->mlx, color);
	i = x * 4 + y * e->size_line;
	e->data[i] = (new_color & 0xFF);
	e->data[i + 1] = (new_color & 0xFF00) >> 8;
	e->data[i + 2] = (new_color & 0xFF0000) >> 16;
	return 0;
}

void 	drawGradient(t_env *e)
{
	int x = 0;
	int y = 0;
	int color = 0xFF0000;
	int r = 0xFF;
	int g = 0x00;
	int b = 0x42;
	while (y < HEIGTH){
		while (x < WIDTH){
			img_pixel_put(e, x, y, color);
			x++;
		}
		if (y % 2 == 0){
			if (r < 0xFF)
				r++;
			if (g < 0xFF)
				g++;
			if (b < 0xFF)
				b++;
		}
		color = (b) + (g << 8) + (r << 16);
		x = 0;
		y++;
	}
}

void	swap_pos(int *x1, int *y1, int *x2, int *y2)
{
	int tmp_x;
	int tmp_y;

	tmp_x = *x2;
	tmp_y = *y2;
	*x1 = *x2;
	*y1 = *y2;
	*y2 = tmp_y;
	*x2 = tmp_x;	
}

void 	draw_line_mlx(t_env *e, int x1, int y1, int x2, int y2, int z1 ,int z2)
{
	int		x;
	int		y;

	(void)z1;
	(void)z2;
	int line_length = sqrt((x2-x1)*(x2-x1)-(y2-y1)*(y2-y1));
	//int distance_length = abs(z2-z1);
	double step;

	int color_min;
	int color_max;

	if(z1==z2)
	{
		if(z1==0)
		{
			color_min = 0xff0000;
			color_max = 0xff0000;
		}
		if(z1==10)
		{
			color_min = 0xffffff;
			color_max = 0xffffff;
		}
	}
	else
	{
		if(z1==0)
			color_min = 0xff0000;
		if(z1==10)
			color_min = 0xffffff;

		if(z2==0)
			color_max = 0xff0000;
		if(z2==10)
			color_max = 0xffffff;
	}

	int color_current = color_min;

	if (x1 == x2 && y1 == y2)
		return ;
	else if (abs(x2 - x1) >= abs(y2 - y1))
	{
		if (x1 > x2)
			swap_pos(&x1, &y1, &x2, &y2);
		x = x1;
		while (x <= x2)
		{
			if(x2-x1 == 0)
				return ;
			y = y1 + ((y2 - y1) * (x - x1)) / (x2 - x1);
			
			int distance_current = sqrt((x-x1)*(x-x1)-(y-y1)*(y-y1));
			step = distance_current/(double)line_length;
			
			color_current = color_min*step+color_max*(1-step);

			if (img_pixel_put(e, x, y, color_current) == -42)
				return ;
			x++;
		}
	}
	else
	{
		if (y1 > y2)
			swap_pos(&x1, &y1, &x2, &y2);
		y = y1;
		while (y <= y2)
		{
			if(y2-y1 == 0)
				return;
			x = x1 + ((x2 - x1) * (y - y1)) / (y2 - y1);
			// img_pixel_put(e, x, y, 0xff0000) == -42

			int distance_current = sqrt((x-x1)*(x-x1)-(y-y1)*(y-y1));
			step = distance_current/(double)line_length;
			
			color_current = color_min*step+color_max*(1-step);

			if (img_pixel_put(e, x, y, color_current) == -42)
				return ;
			y++;
		}
	}
}

void 	draw_circle(t_env *e, int origin_x, int origin_y, int ray)
{
	int x;
	int y;
	int alpha;

	alpha = 0;
	while (alpha < 180){
		x = origin_x + (ray * cos(alpha));
		y = origin_y + (ray * sin(alpha));
		img_pixel_put(e, x, y, 0xff0000);
		alpha++;
	}
}


void 	clearImg(t_env *e)
{
	int 	x;
	int 	y;

	x = 0;
	y = 0;
	while (y < HEIGTH)
	{
		while (x < WIDTH)
		{
			img_pixel_put(e, x, y, 0x000000);
			x++;
		}
		x = 0;
		y++;
	}
}

int 	expose_hook(t_env *e)
{
	clearImg(e);
	drawGradient(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}