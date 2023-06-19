/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:35:07 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/19 09:24:39 by r                ###   ########.fr       */
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
	new->win = mlx_new_window(new->ptr, win_size_x, win_size_y, "Shallow water");
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
		new->leaf->on_time = rand() % meta[0]->on_dur + 2;
		// printf("on time=%i\n", new->leaf->on_time);
		// printf("off_time=%i\n", new->leaf->on_time);
		new->leaf->off_time = (rand() % meta[0]->off_dur) + meta[0]->min_off;
		// printf("off_time=%i\n", new->leaf->off_time);
		// printf("off time=%i\n", new->leaf->off_time);
		// printf("active=%i\n", new->leaf->active);
		new->leaf = new->leaf->next;
	}
	// meta[0]->frame += meta[0]->min_off;
	new->leaf = leaf0;
}

void	text_display(t_meta *meta)
{
	int	first_line_x;
	int	first_line_y;
	int	space_x;
	int	space_y;

	space_x = 160;
	space_y = 17;
	first_line_x = 22;
	first_line_y = 22;
	
	
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x, first_line_y, RED, "on dur:");
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x + space_x, first_line_y, RED, ft_itoa(meta->on_dur));
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x, first_line_y + space_y, RED, "off dur:");
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x + space_x, first_line_y + space_y, RED, ft_itoa(meta->off_dur));
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x, first_line_y + 2*space_y, RED, "min off dur:");
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x + space_x, first_line_y + 2*space_y, RED, ft_itoa(meta->min_off));
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x, first_line_y + 3*space_y, RED, "frame:");
	mlx_string_put (meta->mlx->ptr, meta->mlx->win, first_line_x + space_x, first_line_y + 3*space_y, RED, ft_itoa(meta->frame));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	random_gray(t_meta **meta)
{
	t_meta *new;
	t_leaf *leaf0;
	int random_intensity;

	new = *meta;
	leaf0 = meta[0]->leaf;
	
	while (new->leaf)
	{
		random_intensity = rand() % SOFT_DROP;
		new->leaf->color = create_trgb(0, random_intensity, random_intensity, random_intensity);
		// printf("random gray=%x\n", new->leaf->color);
		new->leaf = new->leaf->next;
	}
	new->leaf = leaf0;
}

void	draw_pixel(t_meta *meta, int color)
{
	my_mlx_pixel_put(meta->img_data, meta->leaf->x, meta->leaf->y, color);
	my_mlx_pixel_put(meta->img_data, meta->leaf->x + 1, meta->leaf->y, color);
	my_mlx_pixel_put(meta->img_data, meta->leaf->x, meta->leaf->y, color);
	my_mlx_pixel_put(meta->img_data, meta->leaf->x, meta->leaf->y + 1, color);	
}

int	print_grid(t_meta *meta)
{
	t_leaf *leaf0;
	int	color;

	if (meta->frame % 10)
		srand(time(NULL));
	leaf0 = meta->leaf;
	mlx_clear_window(meta->mlx->ptr, meta->mlx->win);
	text_display(meta);
	while(meta->leaf)
	{

		if ((meta->frame - meta->leaf->prevframe_on >= meta->leaf->off_time) && !meta->leaf->active)
		{
			random_gray(&meta);
			meta->leaf->active = 1;
			meta->leaf->prevframe_on = meta->frame;
			meta->leaf->off_time = (rand() % meta->off_dur) + meta->min_off;
		}
		else if ((meta->frame - meta->leaf->prevframe_on >= meta->leaf->on_time) && meta->leaf->active)
		{
			meta->leaf->active = 0;
			meta->leaf->on_time = rand() % meta->on_dur + 2;
			meta->leaf->prevframe_on = meta->frame;
		}
		if (meta->leaf->active)
			draw_pixel(meta, meta->leaf->color);
		else
			draw_pixel(meta, GRAY);
		meta->leaf = meta->leaf->next;
	}
	draw_disc((ROW / 2) * meta->spacing + ROW, (COL / 2) * meta->spacing + COL, (ROW / 2) * meta->spacing + ROW / 2, BLACK, meta);
	draw_circle((ROW / 2) * meta->spacing + ROW, (COL / 2) * meta->spacing + COL, (ROW / 2) * meta->spacing + ROW / 2, GRAY, meta);
	meta->frame++;
	meta->leaf = leaf0;

	mlx_put_image_to_window(meta->mlx->ptr, meta->mlx->win, meta->img_data->img, 0, 100);

	// mlx_destroy_image(meta->mlx->ptr, meta->img_data->img);
	// my_new_mlx_img_data(meta);
	return (1);
}