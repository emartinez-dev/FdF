/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:03:55 by franmart          #+#    #+#             */
/*   Updated: 2022/12/13 18:07:38 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

int	count_cols(char *line)
{
	char	*clean_line;
	char	**cells;
	int		i;

	i = 0;
	clean_line = ft_strtrim(line, "\n ");
	free(line);
	cells = ft_split(clean_line, ' ');
	free(clean_line);
	while (cells[i])
		i++;
	double_free(cells);
	return (i);
}

void	map_dimensions(char *filename, t_map *map)
{
	int		fd;
	int		cols;
	char	*line;

	map->height = 0;
	map->width = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
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
	free(line);
	close(fd);
}

void	map_init(char *filename, t_map *map)
{
	int	row;

	row = 0;
	map_dimensions(filename, map);
	map->map = ft_calloc(map->height, sizeof(t_point *));
	while (row < map->height)
	{
		map->map[row] = ft_calloc(map->width, sizeof(t_point));
		row++;
	}
}
