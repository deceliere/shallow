/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdecelie <rdecelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:47:21 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/17 19:40:00 by rdecelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"

t_leaf *add_to_list(int x, int y)
{
	t_leaf *new; ///

	
	// leaf = leaf->next;
	new = malloc(sizeof(t_leaf));
	if (new == NULL)
		return (free(new), NULL);
	new->x = x;
	new->y = y;
	new->active = 0;
	new->prevframe = 0;
	new->currframe = 0;
	new->next = NULL;
	new->down = NULL;
	return(new);
	

}

t_leaf init_list(int x, int y)
{
	t_leaf t;
	
	t.leaf = add_to_list(22, 3);
	t.x = x;
	t.y = y;
	t.active = 0;
	t.prevframe = 0;
	t.currframe = 0;
	t.next = NULL;
	t.down = NULL;
	t.leaf0 = t.leaf;
	t.leaf_line0 = t.leaf;

	return (t);
}

void	print_list(t_leaf *leaf)
{
	t_leaf *tmp;

	tmp = leaf;
	while(tmp)
	{
		printf("list_xy=%i %i\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}
}

t_meta *create_list(t_meta *meta)
{
	t_leaf t0;
	int	tab[10];
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i < 10)
	{
		tab[i] = i;
		i++;
	}

	// t0 = malloc(sizeof(t_leaf));
	// t0.leaf0 = meta->leaf;
	t0 = init_list(11, 33);
	// printf("meta_leaf xy=%i %i\n", t0.x, t0.y);
	while(y < 10)
	{
		t0.next = add_to_list(x, y);
		printf("t0_leaf xy=%i %i\n", t0.next->x, t0.next->y);
		t0.leaf = t0.leaf->next;
		// meta->leaf = meta->leaf->next;
		y++;
	}
	print_list(&t0);


	return (meta);
}


int main()
{
	t_meta  *meta;
	t_leaf	*leaf;

	meta = malloc(sizeof(t_meta));
	meta->i = 0;
	meta = create_list(meta);



	mlx_start(meta);
	mlx_hook(meta->mlx->win, 2, 2, keypress, meta);
	mlx_loop_hook(meta->mlx->ptr, pixel_move, meta);
	mlx_loop(meta->mlx->ptr);
	return (0);
}