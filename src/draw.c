/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 21:01:25 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>

void clear_background(t_fdf *fdf)
{
	mlx_delete_image(fdf->mlx, fdf->g_img);
	fdf->g_img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
}

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

void	bresenham(t_point p0, t_point p1, mlx_image_t *img)
{
	int	dx;
	int	dy;
	int	error;
	int	sx;
	int	sy;

	sx = p0.x < p1.x ? 1 : -1;
	sy = p0.y < p1.y ? 1 : -1;
	dx = abs(p1.x - p0.x);
	dy = -abs(p1.y - p0.y);
	error = dx + dy;
	while (1)
	{
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		if (pixel_limits(&p0))
			mlx_put_pixel(img, p0.x, p0.y, p0.color);
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

void	draw_map(t_fdf *fdf)
{
	unsigned int	i;
	unsigned int	width;
	t_point			pt;
	t_point			*pts;

	clear_background(fdf);
	i = -1;
	pts = fdf->map->points;
	width = fdf->map->width;
	while (++i < fdf->map->len)
	{
		pt = project_pt(fdf->map->points[i], fdf);
		if (i % width != fdf->map->width - 1)
			bresenham(pt, project_pt(pts[i + 1], fdf), fdf->g_img);
		if (i + width < fdf->map->len)
			bresenham(pt, project_pt(pts[i + width], fdf), fdf->g_img);
	}
	mlx_image_to_window(fdf->mlx, fdf->g_img, 0, 0);
}
