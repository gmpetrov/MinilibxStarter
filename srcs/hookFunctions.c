/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookFunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmp <gmp@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 12:47:30 by gmp               #+#    #+#             */
/*   Updated: 2015/02/27 12:49:29 by gmp              ###   ########.fr       */
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

void 	drawGradient(t_env *e)
{
	int 		x;
	int 		y;
	t_color 	c;

	c.r = 0xFF;
	c.g = 0x00;
	c.b = 0x42;
	x = -1;
	y = -1;
	while (++y < HEIGTH)
	{
		while (++x < WIDTH)
			img_pixel_put(e, x, y, e->color);
		if (y % 2 == 0)
		{
			if (c.r < 0xFF)
				c.r++;
			if (c.g < 0xFF)
				c.g++;
			if (c.b < 0xFF)
				c.b++;
		}
		e->color = (c.b) + (c.g << 8) + (c.r << 16);
		x = 0;
	}
}

int 	expose_hook(t_env *e)
{
	clearImg(e);
	drawGradient(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

// void 	draw_line_mlx(t_env *e, t_point a, t_point b)
// {
// 	int		x;
// 	int		y;

// 	(void)a.z;
// 	(void)b.z;
// 	int line_length = sqrt((b.x-a.x)*(b.x-a.x)-(b.y-a.y)*(b.y-a.y));
// 	//int distance_length = abs(b.z-a.z);
// 	double step;

// 	int color_min;
// 	int color_max;

// 	if(a.z==b.z)
// 	{
// 		if(a.z==0)
// 		{
// 			color_min = 0xff0000;
// 			color_max = 0xff0000;
// 		}
// 		if(a.z==10)
// 		{
// 			color_min = 0xffffff;
// 			color_max = 0xffffff;
// 		}
// 	}
// 	else
// 	{
// 		if(a.z==0)
// 			color_min = 0xff0000;
// 		if(a.z==10)
// 			color_min = 0xffffff;

// 		if(b.z==0)
// 			color_max = 0xff0000;
// 		if(b.z==10)
// 			color_max = 0xffffff;
// 	}

// 	int color_current = color_min;

// 	if (a.x == b.x && a.y == b.y)
// 		return ;
// 	else if (abs(b.x - a.x) >= abs(b.y - a.y))
// 	{
// 		if (a.x > b.x)
// 			swap_pos(&a.x, &a.y, &b.x, &b.y);
// 		x = a.x;
// 		while (x <= b.x)
// 		{
// 			if(b.x-a.x == 0)
// 				return ;
// 			y = a.y + ((b.y - a.y) * (x - a.x)) / (b.x - a.x);
			
// 			int distance_current = sqrt((x-a.x)*(x-a.x)-(y-a.y)*(y-a.y));
// 			step = distance_current/(double)line_length;
			
// 			color_current = color_min*step+color_max*(1-step);

// 			if (img_pixel_put(e, x, y, color_current) == -42)
// 				return ;
// 			x++;
// 		}
// 	}
// 	else
// 	{
// 		if (a.y > b.y)
// 			swap_pos(&a.x, &a.y, &b.x, &b.y);
// 		y = a.y;
// 		while (y <= b.y)
// 		{
// 			if(b.y-a.y == 0)
// 				return;
// 			x = a.x + ((b.x - a.x) * (y - a.y)) / (b.y - a.y);
// 			// img_pixel_put(e, x, y, 0xff0000) == -42

// 			int distance_current = sqrt((x-a.x)*(x-a.x)-(y-a.y)*(y-a.y));
// 			step = distance_current/(double)line_length;
			
// 			color_current = color_min*step+color_max*(1-step);

// 			if (img_pixel_put(e, x, y, color_current) == -42)
// 				return ;
// 			y++;
// 		}
// 	}
// }
