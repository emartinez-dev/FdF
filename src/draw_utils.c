/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:35:32 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 17:38:42 by franmart         ###   ########.fr       */
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

void	init_bresenham(t_point p0, t_point p1, t_bresenham *bres)
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
