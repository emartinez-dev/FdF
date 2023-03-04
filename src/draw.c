/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2023/03/04 13:40:58 by franmart         ###   ########.fr       */
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

void	bresenham(t_point p0, t_point p1, mlx_image_t *img, t_map *map)
{
	int	dx;
	int	dy;
	int	error;
	int	sx;
	int	sy;

	isometric(&p0, map);
	isometric(&p1, map);
	sx = p0.x < p1.x ? 1 : -1;
	sy = p0.y < p1.y ? 1 : -1;
	dx = abs(p1.x - p0.x);
	dy = -abs(p1.y - p0.y);
	error = dx + dy;
	while (1)
	{
		if (pixel_limits(&p0))
			mlx_put_pixel(img, p0.x, p0.y, p0.color);
		//mlx_put_pixel(img, p0.x, p0.y, p0.color);
		if (p0.x == p1.x && p0.y == p1.y) break;
		if (2 * error >= dy)
		{
			if (p0.x == p1.x) break;
			error += dy;
			p0.x += sx;
		}
		if (2 * error <= dx)
		{
			if (p0.y == p1.y) break;
			error += dx;
			p0.y += sy;
		}
	}
}

void	world_center(t_map *map)
{
	map->world_x = WIDTH / 2;
	map->world_y = HEIGHT / 2;
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

	//printf("Antes: pixel: x%dy%d\n", p->x, p->y);
	x = (p->x - p->y) * cos(ISO_ANGLE)
		- map->origin_x + map->world_x;
	y = ((p->x + p->y) * sin(ISO_ANGLE) - p->z)
		- map->origin_y + map->world_y;
	p->x = x;
	p->y = y;
	//printf("Despues: pixel: x%dy%d\n", p->x, p->y);
}

void	draw_map(t_map *map, mlx_image_t *g_img, mlx_t *mlx)
{
	unsigned int	i;

	i = 0;
	world_center(map);
	origin_point(map, map->points[
		(map->width / 2 + map->height / 2 * map->width)]);
	while (i < map->len)
	{
		if (map->points[i].x < (map->width - 1) * map->zoom)
			bresenham(map->points[i], map->points[i + 1], g_img, map);
		if (map->points[i].y < (map->height - 1) * map->zoom)
			bresenham(map->points[i], map->points[i + map->width], g_img, map);
		i++;
	}
	mlx_image_to_window(mlx, g_img, 0, 0);
}