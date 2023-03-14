/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 18:04:08 by franmart         ###   ########.fr       */
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
	fd = check_filename(filename);
	line = ft_gnl(fd);
	while (line)
	{
		width = count_cols(line, ' ');
		free(line);
		if (map->height == 0)
			map->width = width;
		if (map->width != width)
			ft_exit(ERR_MAPWIDTH);
		map->height++;
		line = ft_gnl(fd);
	}
	free(line);
	close(fd);
	map->len = map->height * map->width;
	if (map->len == 0)
		ft_exit(ERR_MAPEMPTY);
	map->points = ft_calloc(map->len, sizeof(t_point));
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

int	check_filename(char *filename)
{
	int	fd;

	if (!ft_strnstr(filename, ".fdf", ft_strlen(filename)))
		ft_exit(ERR_FILEEXT);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit(ERR_FILEOPEN);
	ft_printf("Calculating map size...");
	return (fd);
}

float	scale_map(t_map *map)
{
	float	x;
	float	y;
	float	scale;

	x = WIDTH / map->width;
	y = HEIGHT / map->height;
	scale = fminf(x, y);
	return (scale);
}
