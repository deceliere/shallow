/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:35:07 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/18 10:28:46 by r                ###   ########.fr       */
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
	my_mlx_pixel_put(meta->img_data, 100, meta->i, rand());
	my_mlx_pixel_put(meta->img_data, 200, meta->i + 20, rand());
	mlx_put_image_to_window(meta->mlx->ptr,
		meta->mlx->win, meta->img_data->img, 0, 0);
	mlx_destroy_image(meta->mlx->ptr, meta->img_data->img);
	my_new_mlx_img_data(meta);
	if (meta->i == 200)
		meta->i = 0;
	return (1);
}

void	random_time(t_meta **meta)
{
	t_meta *new;
	t_leaf *leaf0;

	new = *meta;
	leaf0 = meta[0]->leaf;
	
	while (new->leaf)
	{
		new->leaf->on_time = rand() % ON_DUR + 2;
		printf("on time=%i\n", new->leaf->on_time);
		new->leaf->off_time = (rand() % OFF_DUR) + MIN_OFF_DUR;
		printf("off time=%i\n", new->leaf->off_time);
		// printf("active=%i\n", new->leaf->active);
		new->leaf = new->leaf->next;
	}
	new->leaf = leaf0;
}

int	print_grid(t_meta *meta)
{
	t_leaf *leaf0;
	int	color;

	leaf0 = meta->leaf;
	random_time(&meta);

	mlx_clear_window(meta->mlx->ptr, meta->mlx->win);

	printf("leaf actif xy=%i %i  %i\n", meta->leaf->x, meta->leaf->y, meta->leaf->active);
	
	while(meta->leaf)
	{

		// color = random_color;
		// printf("random color=%i\n", color);
		if ((meta->leaf->frame - meta->leaf->prevframe_on >= meta->leaf->off_time) && !(meta->leaf->active))
		{
			if (!meta->leaf->next)
				printf("time off\n");
			meta->leaf->active = 1;
			meta->leaf->prevframe_on = meta->leaf->frame;
		}
		else if ((meta->leaf->frame - meta->leaf->prevframe_on >= meta->leaf->on_time) && (meta->leaf->active))
		{
			if (!meta->leaf->next)
				printf("time on\n");
			meta->leaf->active = 0;
			meta->leaf->prevframe_on = meta->leaf->frame;
		}
		if (meta->leaf->active)
			my_mlx_pixel_put(meta->img_data, meta->leaf->x, meta->leaf->y, WHITE);
		meta->leaf->frame++;
		meta->leaf->currframe_on = meta->leaf->frame;
		meta->leaf->currframe_off = meta->leaf->frame;
		if (!meta->leaf->next)
			printf("frame=%li\n", meta->leaf->frame);
		meta->leaf = meta->leaf->next;
	}
	meta->leaf = leaf0;
	mlx_put_image_to_window(meta->mlx->ptr,
		meta->mlx->win, meta->img_data->img, 0, 0);
	mlx_destroy_image(meta->mlx->ptr, meta->img_data->img);
	my_new_mlx_img_data(meta);
	// if (meta->i == 200)
		// meta->i = 0;
	return (1);
}