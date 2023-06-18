/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:00:59 by r                 #+#    #+#             */
/*   Updated: 2023/06/18 15:08:22 by r                ###   ########.fr       */
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
		// putpixel(x + x1, y + y1, color);
		my_mlx_pixel_put(meta->img_data, x + x1, y + y1, WHITE);
	}
	// mlx_put_image_to_window(meta->mlx->ptr,
		// meta->mlx->win, meta->img_data->img, 0, 0);
	// mlx_destroy_image(meta->mlx->ptr, meta->img_data->img);
	// my_new_mlx_img_data(meta);
}

 