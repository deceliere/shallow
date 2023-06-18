/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:00:59 by r                 #+#    #+#             */
/*   Updated: 2023/06/18 15:47:20 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"

void draw_circle(int x, int y, int r, int color, t_meta *meta)
{
	// mlx_clear_window(meta->mlx->ptr, meta->mlx->win);

	static const double PI = 3.1415926535;
	double i, angle, x1, y1;
	for(i = 0; i < 360; i += 0.1)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		my_mlx_pixel_put(meta->img_data, x + x1, y + y1, color);
	}
}

void draw_disc(int x, int y, int r, int color, t_meta *meta)
{
	static const double PI = 3.1415926535;
	double i, angle, x1, y1;
	for(i = 0; i < 360; i += 0.1)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		if (i <= 90 || i >= 270)
			for (int j = 0; j < WIDTH; j++)
				my_mlx_pixel_put(meta->img_data, x + x1 + j, y + y1, color);
		else if (i > 90 && i < 270)
			for (int j = 0; j < x + x1 - 1; j++)
				my_mlx_pixel_put(meta->img_data, j, y + y1, color);
	}
}

 