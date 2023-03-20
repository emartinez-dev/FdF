/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:44:55 by franmart          #+#    #+#             */
/*   Updated: 2023/03/20 09:34:45 by franmart         ###   ########.fr       */
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
	rotate_x(&pt, fdf);
	rotate_y(&pt, fdf);
	rotate_z(&pt, fdf);
	if (fdf->cam->projection == ISOMETRIC)
	{
		x = (pt.x - pt.y) * cos(ISO_ANGLE);
		y = (-pt.z + (pt.x + pt.y)) * sin(ISO_ANGLE);
	}
	else
	{
		x = pt.x;
		y = pt.y;
	}
	pt.x = x + WIDTH / 2 + fdf->cam->offset_x;
	pt.y = y + (HEIGHT + fdf->map->height) / 2 + fdf->cam->offset_y;
	return (pt);
}

void	rotate_x(t_point *pt, t_fdf *fdf)
{
	int	y;
	int	z;

	if (fdf->cam->x_angle == 0)
		return ;
	y = pt->y;
	z = pt->z;
	pt->y = y * cos(fdf->cam->x_angle) + z * sin(fdf->cam->x_angle);
	pt->z = -y * sin(fdf->cam->x_angle) + z * cos(fdf->cam->x_angle);
}

void	rotate_y(t_point *pt, t_fdf *fdf)
{
	int	x;
	int	z;

	if (fdf->cam->y_angle == 0)
		return ;
	x = pt->x;
	z = pt->z;
	pt->x = x * cos(fdf->cam->y_angle) + z * sin(fdf->cam->y_angle);
	pt->z = -x * sin(fdf->cam->y_angle) + z * cos(fdf->cam->y_angle);
}

void	rotate_z(t_point *pt, t_fdf *fdf)
{
	int	x;
	int	y;

	if (fdf->cam->z_angle == 0)
		return ;
	x = pt->x;
	y = pt->y;
	pt->x = x * cos(fdf->cam->z_angle) - y * sin(fdf->cam->z_angle);
	pt->y = x * sin(fdf->cam->z_angle) + y * cos(fdf->cam->z_angle);
}
