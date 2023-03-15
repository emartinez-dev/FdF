/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 17:41:08 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
			bresenham(pt, project_pt(pts[i + 1], fdf), fdf->img);
		if (i + width < fdf->map->len)
			bresenham(pt, project_pt(pts[i + width], fdf), fdf->img);
	}
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
}

void	bresenham(t_point p0, t_point p1, mlx_image_t *img)
{
	t_bresenham	bres;

	init_bresenham(p0, p1, &bres);
	while (1)
	{
		if (p0.x == p1.x && p0.y == p1.y)
			return ;
		if (pixel_limits(&p0))
			mlx_put_pixel(img, p0.x, p0.y, interpolate_color(p0, p1, bres));
		if (2 * bres.error >= bres.dy)
		{
			if (p0.x == p1.x)
				return ;
			bres.error += bres.dy;
			p0.x += bres.sx;
		}
		if (2 * bres.error <= bres.dx)
		{
			if (p0.y == p1.y)
				return ;
			bres.error += bres.dx;
			p0.y += bres.sy;
		}
	}
}

void	draw_instructions(t_fdf *fdf)
{
	fdf->help_on = 0;
	fdf->help = mlx_put_string(fdf->mlx, I_INTRO, 10, 20);
	fdf->help = mlx_put_string(fdf->mlx, I_QUIT, 10, 40);
	fdf->help = mlx_put_string(fdf->mlx, I_CLOSE_HELP, 10, 60);
	fdf->help = mlx_put_string(fdf->mlx, I_MOVE, 10, 80);
	fdf->help = mlx_put_string(fdf->mlx, I_ZOOM, 10, 100);
	fdf->help = mlx_put_string(fdf->mlx, I_ISO, 10, 120);
	fdf->help = mlx_put_string(fdf->mlx, I_ZSCALE, 10, 140);
	fdf->help->enabled = 0;
}
