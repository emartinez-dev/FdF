/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:34:40 by franmart          #+#    #+#             */
/*   Updated: 2022/12/17 17:47:26 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

void	draw_line(t_point *p0, t_point *p1, mlx_image_t *img)
{
	float	a;
	float	y;

	a = (p1->y - p0->y) / (p1->x - p0->x);
	while (p0->x < p1->x)
	{
		mlx_put_pixel(img, p0->x, p0->y, 255);
		p0->y += a;
	}
}