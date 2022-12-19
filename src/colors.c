/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:42:09 by franmart          #+#    #+#             */
/*   Updated: 2022/12/19 18:11:47 by franmart         ###   ########.fr       */
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
		color = ft_atoi_base(arr[1], "0123456789abcdef");
		color = dec_to_rgba(color);
		free_array(arr);
	}
	else
		color = 128;
	return (color);
}

unsigned int	dec_to_hex(unsigned int n)
{
	unsigned int	hex;
	unsigned int	base;
	unsigned int	remainder;

	hex = 0;
	base = 1;
	while (n > 0)
	{
    	remainder = n % 16;
    	n /= 16;
    	hex += remainder * base;
    	base *= 10;
	}
	return hex;
}

unsigned int	dec_to_rgba(unsigned int n)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	hex;

	hex = dec_to_hex(n);
	r = (hex & 0xff000000) >> 24;
	g = (hex & 0xff0000) >> 16;
	b = (hex & 0xff00) >> 8;
	return ((r << 16) | (g << 8) | b);
}
