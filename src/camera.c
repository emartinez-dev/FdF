/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:23:11 by franmart          #+#    #+#             */
/*   Updated: 2023/03/17 12:30:48 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	init_cam(t_fdf *fdf)
{
	fdf->cam = ft_calloc(1, sizeof(t_cam));
	fdf->cam->projection = ISOMETRIC;
	fdf->cam->zoom = fminf((WIDTH / fdf->map->width), \
		(HEIGHT / fdf->map->height)) / 2;
	fdf->cam->z_scale = 1;
	fdf->cam->offset_x = 0;
	fdf->cam->offset_y = 0;
	fdf->cam->x_angle = 0;
	fdf->cam->y_angle = 0;
	fdf->cam->z_angle = 0;
}

void	reset_cam(t_fdf *fdf)
{
	fdf->cam->offset_x = 0;
	fdf->cam->offset_y = 0;
	fdf->cam->x_angle = 0;
	fdf->cam->y_angle = 0;
	fdf->cam->z_angle = 0;
	fdf->cam->zoom = fminf((WIDTH / fdf->map->width), \
		(HEIGHT / fdf->map->height)) / 2;
	fdf->cam->z_scale = 1;
}
