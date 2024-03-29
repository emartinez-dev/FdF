/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:03:55 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 22:39:00 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_map	*map_init(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->points = NULL;
	map->len = 0;
	map->width = 0;
	map->height = 0;
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	return (map);
}

void	map_free(t_map *map)
{
	free(map->points);
	free(map);
}

int	count_cols(char *line, char sep)
{
	int	i;
	int	cols;

	i = 0;
	cols = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == sep)
		{
			while (line[i] && (line[i] == sep || line[i] == '\n'))
				i++;
		}
		else
		{
			while (line[i] && line[i] != sep)
				i++;
			cols++;
		}
	}
	ft_printf(".");
	return (cols);
}
