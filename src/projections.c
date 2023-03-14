/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:44:55 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 20:49:04 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* This function takes a point and resizes it depending on the map width and
height, projects it on an isometrical plane and adjusts it to the middle of
the screen */
t_point	project_pt(t_point pt, t_fdf *fdf)
{
	int	x;
	int	y;

	pt.x = pt.x * fdf->cam->zoom - ((fdf->map->width * fdf->cam->zoom) / 2);
	pt.y = pt.y * fdf->cam->zoom - ((fdf->map->height * fdf->cam->zoom) / 2);
	pt.z = pt.z * fdf->cam->zoom / fdf->cam->z_scale;
	x = (pt.x - pt.y) * cos(ISO_ANGLE);
	y = (-pt.z + (pt.x + pt.y)) * sin(ISO_ANGLE);
	pt.x = x + WIDTH / 2 + fdf->cam->offset_x;
	pt.y = y + (HEIGHT + fdf->map->height) / 2 + fdf->cam->offset_y;
	return (pt);
}
