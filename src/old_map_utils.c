/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:03:55 by franmart          #+#    #+#             */
/*   Updated: 2022/12/14 17:52:49 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

int	count_cols(char *line)
{
	char	**cells;
	int		i;

	i = 0;
	cells = ft_split(line, ' ');
	free(line);
	while (cells[i] && cells[i][0] != '\n')
		i++;
	free_array(cells);
	return (i);
}

void	map_measure(char *filename, t_map *map)
{
	int		fd;
	int		cols;
	char	*line;

	map->height = 0;
	map->width = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line != NULL)
	{
		cols = count_cols(line);
		if (map->height == 0)
			map->width = cols;
		else
			if (map->width != cols)
				exit(2);
		map->height++;
		line = ft_gnl(fd);
	}
	close(fd);
}

void	map_alloc(char *filename, t_map *map)
{
	int	row;

	row = 0;
	map_measure(filename, map);
	map->points = ft_calloc(map->height, sizeof(t_point *));
	while (row < map->height)
	{
		map->points[row] = ft_calloc(map->width, sizeof(t_point));
		row++;
	}
}

void	map_free(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
}
