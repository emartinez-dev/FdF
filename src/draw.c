/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2022/12/19 15:55:15 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	isometric(t_point *point)
{
	float	x1;
	float	y1;

	x1 = (point->x - point->y) * cos(ANGLE);
	y1 = (point->x + point->y) * sin(ANGLE) - point->z;
	//ft_printf("x_og: %d\ty_og: %d\n", point->x, point->y);
	point->x = x1;
	point->y = y1;
	//ft_printf("x_new: %d\ty_new:%d\n\n", point->x, point->y);
}

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

	//isometric(&p0);
	//isometric(&p1);
	sx = p0.x < p1.x ? 1 : -1;
	sy = p0.y < p1.y ? 1 : -1;
	dx = abs(p1.x - p0.x);
	dy = -abs(p1.y - p0.y);
	error = dx + dy;
	while (1)
	{
		if (pixel_limits(&p0))
			mlx_put_pixel(img, p0.x, p0.y, 255);
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

void	draw_map(t_map *map, mlx_image_t *g_img, mlx_t *mlx)
{
	int	i;

	i = 0;
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