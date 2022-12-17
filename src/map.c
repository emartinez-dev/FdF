/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2022/12/17 13:08:07 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

/* Calculates the map size and allocates the memory for it */
void	map_init(char *filename, t_map *map)
{
	char	*line;
	int		width;
	int		fd;

	map->height = 0;
	ft_printf("Calculating map size...");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = ft_gnl(fd);
	while (line)
	{
		width = count_cols(line, ' ');
		if (map->height == 0)
			map->width = width;
		if (map->width != width)
			exit(2);
		map->height++;
		free(line);
		line = ft_gnl(fd);
	}
	free(line);
	map->len = map->height * map->width;
	map->points = ft_calloc(map->height * map->width, sizeof(t_point));
	close(fd);
}

/* Fill the points of the map */
void	map_fill(char *filename, t_map *map)
{
	unsigned int	i;
	int				fd;
	char			*line;
	char			**cols;

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

int	main(int argc, char **argv)
{
	t_map	map;
	int		i;

	// hay que validar la entrada
	map_init(argv[1], &map);
	//ft_printf("Alto: %d\nAncho: %d\nLongitud: %d\n\n", map.height, map.width, map.len);
	i = map.len - 1;
	map_fill(argv[1], &map);
	ft_printf("X:%d\tY:%d\tZ:%d\t\n", map.points[i].x,
		map.points[i].y, map.points[i].z);
	/*
	while (i < map.len)
	{
		ft_printf("X:%d\tY:%d\tZ:%d\t\n", map.points[i].x,
			map.points[i].y, map.points[i].z);
		i++;
	}
	*/
	return (0);
}
