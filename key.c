/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdecelie <rdecelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:35:02 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/17 17:40:09 by rdecelie         ###   ########.fr       */
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
	if (key == KEY_ESC)
		keypress_esc(meta);
	// render_map(meta);
	return (0);
}