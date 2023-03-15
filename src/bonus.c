/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:11:57 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 21:31:48 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>
#include <time.h>

void	rainbow_mode(t_map *map)
{
	unsigned int	i;

	srand(time(NULL));
	i = -1;
	while (++i < map->len)
		map->points[i].color = random_color(rand() % 255, rand() % 255, \
			rand() % 255);
}

void	bonus_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_HOME))
	{
		rainbow_mode(fdf->map);
		draw_map(fdf);
	}
}

uint32_t	random_color(char r1, char g1, char b1)
{
	int	r;
	int	g;
	int	b;

	r = (r1 >> 24) & 0xFF;
	g = (g1 >> 16) & 0xFF;
	b = (b1 >> 8) & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}
