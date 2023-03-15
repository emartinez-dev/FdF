/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:42:09 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 13:08:12 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

unsigned int	get_color(char *line)
{
	char			**arr;
	unsigned int	color;

	if (ft_strchr(line, ',') != NULL)
	{
		arr = ft_split(line, ',');
		if (arr && arr[1])
			color = ft_atoi_base(arr[1], "0123456789abcdef");
		else
			color = 0;
		color = (color << 8) | 0xff;
		color = hex_to_rgba(color);
		ft_free_array(arr);
	}
	else
		color = hex_to_rgba(0x000000FF);
	return (color);
}

uint32_t	hex_to_rgba(unsigned int hex)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (hex >> 24) & 0xFF;
	g = (hex >> 16) & 0xFF;
	b = (hex >> 8) & 0xFF;
	a = hex & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	interpolate(int a, int b, float factor)
{
	return (a * (1 - factor) + (b * factor));
}

uint32_t	interpolate_color(t_point p0, t_point p1, t_bresenham bres)
{
	int			r;
	int			g;
	int			b;
	int			a;
	float		step;

	if (p0.color == p1.color)
		return (p0.color);
	step = (float)(p0.x - bres.init_x) / (float)(p1.x - bres.init_x);
	r = interpolate((p0.color >> 24) & 0xFF, (p1.color >> 24) & 0xFF, step);
	g = interpolate((p0.color >> 16) & 0xFF, (p1.color >> 16) & 0xFF, step);
	b = interpolate((p0.color >> 8) & 0xFF, (p1.color >> 8) & 0xFF, step);
	a = interpolate(p0.color & 0xFF, p1.color & 0xFF, step);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
