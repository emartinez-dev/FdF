/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 16:41:26 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clear_background(t_fdf *fdf)
{
	fdf->img->pixels = ft_memset(fdf->img->pixels, 100, WIDTH * HEIGHT * 4);
}

int	pixel_limits(t_point *point)
{
	if (point->x < 0 || point->x > WIDTH)
		return (0);
	if (point->y < 0 || point->y > HEIGHT)
		return (0);
	return (1);
}

void	bresenham(t_point p0, t_point p1, mlx_image_t *img)
{
	t_bresenham	bres;

	calc_initial_bresenham(p0, p1, &bres);
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

void	calc_initial_bresenham(t_point p0, t_point p1, t_bresenham *bres)
{
	if (p0.x < p1.x)
		bres->sx = 1;
	else
		bres->sx = -1;
	if (p0.y < p1.y)
		bres->sy = 1;
	else
		bres->sy = -1;
	bres->dx = abs(p1.x - p0.x);
	bres->dy = -abs(p1.y - p0.y);
	bres->error = bres->dx + bres->dy;
	bres->init_x = p0.x;
	bres->init_y = p0.y;
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
			bresenham(pt, project_pt(pts[i + 1], fdf), fdf->img);
		if (i + width < fdf->map->len)
			bresenham(pt, project_pt(pts[i + width], fdf), fdf->img);
	}
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
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
