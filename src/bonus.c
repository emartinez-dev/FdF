/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:11:57 by franmart          #+#    #+#             */
/*   Updated: 2023/03/17 12:25:25 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>
#include <time.h>

void	rainbow_mode(t_map *map)
{
	unsigned int	i;
	uint32_t		rand_col;

	srand(time(NULL));
	i = -1;
	rand_col = random_color(rand() % 255, rand() % 255, \
			rand() % 255) / (map->max_z + map->min_z);
	while (++i < map->len)
		map->points[i].color = rand_col * map->points[i].z;
}

void	bonus_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
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
