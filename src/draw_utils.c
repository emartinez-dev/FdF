/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:35:32 by franmart          #+#    #+#             */
/*   Updated: 2023/03/20 09:28:32 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clear_background(mlx_image_t *img)
{
	img->pixels = ft_memset(img->pixels, 100, img->height * img->width * 4);
}

int	pixel_limits(t_point *point)
{
	if (point->x < 1 || point->x > WIDTH - 1)
		return (0);
	if (point->y < 1 || point->y > HEIGHT - 1)
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
