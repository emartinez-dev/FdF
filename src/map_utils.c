/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:03:55 by franmart          #+#    #+#             */
/*   Updated: 2022/12/18 10:51:02 by franmart         ###   ########.fr       */
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
		map->points[start_index + i].x = i * ZOOM;
		map->points[start_index + i].y = line_n * ZOOM;
		map->points[start_index + i].z = ft_atoi(cols[i]) * 2;
		// TODO: implement color loading
		// load_color(cols[i]);
		//map->points[start_index + i].color = i;
		i++;
	}
	free_array(cols);
}
