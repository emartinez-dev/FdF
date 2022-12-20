/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:03:55 by franmart          #+#    #+#             */
/*   Updated: 2022/12/20 22:49:56 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	map_free(t_map *map)
{
	int	i;

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
	free_array(cols);
}

void	map_zoom(t_map *map)
{
	int	width_zoom;
	int	height_zoom;

	width_zoom = sqrt(WIDTH / map->width / 2);
	height_zoom = sqrt(HEIGHT / map->height / 2);
	ft_printf("\nAncho: %d\tZoom ancho: %d\nAlto: %d\tZoom alto: %d\n",
		map->height, height_zoom, map->width, width_zoom);
	if (width_zoom <= height_zoom)
		map->zoom = height_zoom;
	else
		map->zoom = width_zoom;
	if (map->zoom < 1)
		map->zoom = 1;
	map->z_scale = 1;
}