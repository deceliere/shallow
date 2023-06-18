/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:47:21 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/18 10:28:07 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"

void	add_to_list(t_leaf **head, int x, int y)
{
	t_leaf *new;

	new = malloc(sizeof(t_leaf));
	new->x = x;
	new->y = y;
	new->active = 0;
	new->prevframe_on = 0;
	new->prevframe_off = 0;
	new->currframe_on = 0;
	new->currframe_off = 0;
	new->frame = 0;
	new->on_time = ON_DUR;
	new->off_time = (rand() % OFF_DUR) + MIN_OFF_DUR;
	new->next = NULL;
	new->down = NULL;
	// printf("add to list ok\n");
	*head = new;
}

void	append_to_list(t_leaf **head, int x, int y)
{
	t_leaf	*new;
	t_leaf	*current;
	int	i;

	i = 0;
	new = malloc(sizeof(t_leaf));

	new->x = x;
	new->y = y;
	new->active = 0;
	new->prevframe_on = 0;
	new->prevframe_off = 0;
	new->currframe_on = 0;
	new->currframe_off = 0;
	new->frame = 0;
	new->on_time = ON_DUR;
	new->off_time = (rand() % OFF_DUR) + MIN_OFF_DUR;
	new->next = NULL;
	new->down = NULL;

	// if (*head == NULL)
		// *head = new;
	current = *head;
	while(current->next)
	{
		current = current->next;
		// i++;
		// printf("append to list ok i=%i\n", i);
	}
	current->next = new;
}


void	print_list(t_leaf **leaf)
{
	t_leaf *tmp;

	tmp = *leaf;
	while(tmp)
	{
		printf("list_xy=%i %i\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}
}

void	space_list(t_meta *meta, t_leaf *leaf)
{
	t_leaf *new;

	// new = leaf;
	
	while(leaf)
	{
		leaf->x *= meta->spacing;
		leaf->y *= meta->spacing;
		// new->x *= meta->spacing;
		leaf = leaf->next;
		// printf("meta->spacing=%i\n", meta->spacing);
		// printf("space_xy=%i %i\n", leaf->x, leaf->y);
	}

}

t_meta *create_list(t_meta *meta)
{
	t_leaf *head;
	int	tab[10];
	int	i;
	int	x;
	int	y;

	// i = 0;
	// x = 0;
	// y = 0;
	// while (x < 10)
	// {
	// 	tab[x] = x;
	// 	x++;
	// }


	x = 1;
	y = 1;
	add_to_list(&head, x++, y);
	while(y <= COL)
	{
		while(x <= ROW)
		{
			append_to_list(&head, x, y);
			x++;
		}
		x = 1;
		y++;
	}
	space_list(meta, head);
	// print_list(&head);

	meta->leaf = head;
	return (meta);
}



int main()
{
	t_meta  *meta;
	t_leaf	*leaf;

	srand(time(NULL));
	meta = malloc(sizeof(t_meta));
	meta->i = 0;
	meta->spacing = 30;

	meta = create_list(meta);

	

	
	mlx_start(meta);
	// print_grid(meta);
	mlx_hook(meta->mlx->win, 2, 2, keypress, meta);
	// mlx_loop_hook(meta->mlx->ptr, pixel_move, meta);
	mlx_loop_hook(meta->mlx->ptr, print_grid, meta);
	mlx_loop(meta->mlx->ptr);
	
	
	return (0);
}