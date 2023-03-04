/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:42:09 by franmart          #+#    #+#             */
/*   Updated: 2023/03/04 14:24:21 by franmart         ###   ########.fr       */
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
