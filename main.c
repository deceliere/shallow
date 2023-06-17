/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdecelie <rdecelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:47:21 by rdecelie          #+#    #+#             */
/*   Updated: 2023/06/17 17:59:32 by rdecelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shallow.h"

int main()
{
	t_meta  *meta;

	meta = malloc(sizeof(t_meta));
	meta->i = 0;

	mlx_start(meta);
	mlx_hook(meta->mlx->win, 2, 2, keypress, meta);
	mlx_loop_hook(meta->mlx->ptr, pixel_move, meta);
	mlx_loop(meta->mlx->ptr);
	return (0);
}