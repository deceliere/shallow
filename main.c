/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:47:21 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/20 10:17:19 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"

void	add_to_list(t_leaf **head, int x, int y)
{
	t_leaf *new;

	new = malloc(sizeof(t_leaf));
	new->x = x;
	new->y = y;
	new->active = PIXEL_INITAL_STATE;
	new->prevframe_on = 0;
	new->on_time = ON_DUR;
	new->off_time = (rand() % (OFF_DUR + MIN_OFF_DUR));
	new->next = NULL;
	new->down = NULL;
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
	new->active = PIXEL_INITAL_STATE;
	new->prevframe_on = 0;
	new->on_time = ON_DUR;
	new->off_time = (rand() % (OFF_DUR + MIN_OFF_DUR));
	new->next = NULL;
	new->down = NULL;

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
		printf("list_x=%i \ty=%i \toff_time=%i \tactive=%i\n", tmp->x, tmp->y, tmp->off_time, tmp->active);
		tmp = tmp->next;
	}
}

void	space_list(t_meta *meta, t_leaf *leaf)
{
	t_leaf *new;

	// new = leaf;
	
	while(leaf)
	{
		if (leaf->y % 2)
			leaf->x = leaf->x * meta->spacing + meta->spacing/2;
		else
			leaf->x *= meta->spacing;
		leaf->y = meta->spacing * leaf->y;
		leaf = leaf->next;
	}

}

t_meta *create_list(t_meta *meta)
{
	t_leaf *head;
	int	tab[10];
	int	i;
	int	x;
	int	y;

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


void	random_test(void)
{
	int	i;
	int	tot_positive;
	int	rand_i;

	i = 0;
	tot_positive = 0;
	while(i < 5000)
	{
		
		rand_i = rand() % (1000);
		if (rand_i > 990)
		{
			printf("i=%i rand %i= %i\n", i, INT_MAX , rand_i);
			tot_positive++;
		}
		i++;
	}
	printf("tot_positif=%i\n", tot_positive);
	exit(0);
}

int mtwister(int max) 
{
	static int 	seed = 0;
  	int 		i;
	
	seed++;
  	MTRand r = seedRand(seed);
	i = genRand(&r) * max;
  	return i;
}

int main()
{
	t_meta  *meta;
	t_leaf	*leaf;

	meta = malloc(sizeof(t_meta));
	meta->i = 0;
	meta->spacing = 30;
	meta->frame = 0;
	meta->off_dur = OFF_DUR;
	meta->min_off = MIN_OFF_DUR;
	meta->on_dur = ON_DUR;

	meta = create_list(meta);

	// for (int i = 0; i < 200; i++)
	// {
	// 	printf("%d\n", mtwister(5000));		
	// }
	// exit (0);


	mlx_start(meta);
	// print_grid(meta);
	// draw_circle(200, 200, 50, WHITE, meta);
	mlx_hook(meta->mlx->win, 2, 2, keypress, meta);
	// mlx_loop_hook(meta->mlx->ptr, pixel_move, meta);
	// mlx_string_put (meta->mlx->ptr, meta->mlx->win, 22, 22, RED, " hello");

	mlx_loop_hook(meta->mlx->ptr, print_grid, meta);  
	mlx_loop(meta->mlx->ptr);




	
	
	return (0);
}