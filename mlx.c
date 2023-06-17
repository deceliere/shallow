/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdecelie <rdecelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:35:07 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/17 17:59:32 by rdecelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"


void	my_mlx_pixel_put(t_img *imgdata, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH - 1 || y > HEIGHT -1 || x < 0 || y < 0)
		return ;
	dst = imgdata->addr + (y * imgdata->line_length
			+ x * (imgdata->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_mlx	*mlx_init_struct(int win_size_x, int win_size_y)
{
	t_mlx	*new;

	new = malloc(sizeof(t_mlx));
	if (!new)
		return (NULL);
	new->ptr = mlx_init();
	new->win = mlx_new_window(new->ptr, win_size_x, win_size_y, "Shallow");
	return (new);
}


void	my_new_mlx_img_data(t_meta *meta)
{
	meta->img_data->img = mlx_new_image(meta->mlx->ptr, WIDTH, HEIGHT);
	meta->img_data->addr = mlx_get_data_addr(meta->img_data->img,
			&meta->img_data->bits_per_pixel,
			&meta->img_data->line_length, &meta->img_data->endian);
}



int    mlx_start(t_meta *meta)
{
	meta->mlx = mlx_init_struct(WIDTH, HEIGHT);
	meta->img_data = malloc(sizeof(t_img));
	if (!meta->img_data)
		return (free(meta->img_data), 0);
	my_new_mlx_img_data(meta);
	return (0);
}


int	pixel_move(t_meta *meta)
{
	meta->i++;

	mlx_clear_window(meta->mlx->ptr, meta->mlx->win);
	my_mlx_pixel_put(meta->img_data, 100, meta->i, WHITE);
	mlx_put_image_to_window(meta->mlx->ptr,
		meta->mlx->win, meta->img_data->img, 0, 0);
	mlx_destroy_image(meta->mlx->ptr, meta->img_data->img);
	my_new_mlx_img_data(meta);
	if (meta->i == 200)
		meta->i = 0;
	return (1);
}
