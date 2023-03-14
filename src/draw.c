/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 18:17:43 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>

int	pixel_limits(t_point *point)
{
	if (point->x < 0 || point->x > WIDTH)
		return (0);
	if (point->y < 0 || point->y > HEIGHT)
		return (0);
	return (1);
}

void	origin_point(t_map *map, t_point focal_p)
{
	map->origin_x = (focal_p.x - focal_p.y) * cos(ISO_ANGLE);
	map->origin_y = ((focal_p.x + focal_p.y + 1) * sin(ISO_ANGLE) - focal_p.z);
}

void	isometric(t_point *p, t_map *map)
{
	int	x;
	int	y;

	x = (p->x - p->y) * cos(ISO_ANGLE)
		- map->origin_x + map->world_x;
	y = ((p->x + p->y) * sin(ISO_ANGLE) - p->z)
		- map->origin_y + map->world_y;
	p->x = x;
	p->y = y;
}

void	draw_map(t_map *map, mlx_image_t *g_img, mlx_t *mlx)
{
	origin_point(map, map->points[
		(map->width / 2 + map->height / 2 * map->width)]);
	mlx_image_to_window(mlx, g_img, 0, 0);
}
