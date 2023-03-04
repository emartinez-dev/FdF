/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:03:55 by franmart          #+#    #+#             */
/*   Updated: 2023/03/04 13:40:22 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	map_free(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->len)
	{
		free(&map->points[i]);
		i++;
	}
	free(map->points);
}

int	count_cols(char *line, char sep)
{
	int	i;
	int	cols;

	i = 0;
	cols = 0;
	while (line[i])
	{
		if (line[i] == sep)
		{
			while ((line[i] == sep || line[i] == '\n') && line[i])
				i++;
		}
		else
		{
			while (line[i] != sep && line[i])
				i++;
			cols++;
		}
	}
	ft_printf(".");
	return (cols);
}

void	read_line(char *line, t_map *map, int line_n)
{
	char	**cols;
	int		i;
	int		start_index;

	i = 0;
	start_index = line_n * map->width;
	cols = ft_split(line, ' ');
	ft_printf("#");
	while (cols[i] && cols[i][0] != '\n')
	{
		map->points[start_index + i].x = i * map->zoom;
		map->points[start_index + i].y = line_n * map->zoom;
		map->points[start_index + i].z = ft_atoi(cols[i]) * map->z_scale;
		map->points[start_index + i].color = get_color(cols[i]);
		i++;
	}
	ft_free_array(cols);
}

void	map_zoom(t_map *map)
{
	double	width_zoom;
	double	height_zoom;

	width_zoom = WIDTH / map->width / 2;
	height_zoom = (HEIGHT - 300) / map->height;
	printf("\nAncho: %d\tZoom ancho: %f\nAlto: %d\tZoom alto: %f\n",
		map->height, height_zoom, map->width, width_zoom);
	if (width_zoom <= height_zoom)
		map->zoom = width_zoom;
	else
		map->zoom = height_zoom;
	map->z_scale = 1;
}