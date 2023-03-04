/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2023/03/04 14:14:00 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* Calculates the map size and allocates the memory for it */
void	map_init(char *filename, t_map *map)
{
	unsigned int	width;
	char			*line;
	int				fd;

	map->height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	ft_printf("Calculating map size...");
	line = ft_gnl(fd);
	while (line)
	{
		width = count_cols(line, ' ');
		free(line);
		if (map->height == 0)
			map->width = width;
		if (map->width != width)
			exit(2);
		map->height++;
		line = ft_gnl(fd);
	}
	free(line);
	map->len = map->height * map->width;
	map->points = ft_calloc(map->len, sizeof(t_point));
	close(fd);
}

/* Fill the points of the map */
void	map_fill(char *filename, t_map *map)
{
	unsigned int	i;
	int				fd;
	char			*line;

	map_zoom(map);
	i = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	ft_printf("\nFilling map points -> ");
	while (line)
	{
		read_line(line, map, i);
		free(line);
		line = ft_gnl(fd);
		i++;
	}
	ft_printf("\n");
	free(line);
	close(fd);
}
