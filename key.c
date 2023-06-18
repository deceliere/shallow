/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: r <r@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:35:02 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/18 18:28:22 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"

int	keypress_esc(t_meta *meta)
{
	mlx_destroy_window(meta->mlx->ptr, meta->mlx->win);
	// free_lists(meta);
	exit (0);
}


int	keypress(int key, t_meta *meta)
{
	// printf("key=%i\n", key);
	if (key == KEY_ESC)
		keypress_esc(meta);
	else if (key == KEY_Q)
		meta->on_dur += 1;
	else if (key == KEY_A)
		meta->on_dur -= 1;
	else if (key == KEY_W)
		meta->off_dur += 50;
	else if (key == KEY_S)
		meta->off_dur -= 50;
	else if (key == KEY_E)
		meta->min_off += 100;
	else if (key == KEY_D)
		meta->min_off -= 100;

	
	// render_map(meta);
	return (0);
}