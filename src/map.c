/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 10:59:42 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* Calculates the map size and allocates the memory for it */
void	map_load(char *filename, t_map *map)
{
	unsigned int	width;
	char			*line;
	int				fd;

	fd = check_filename(filename);
	line = ft_gnl(fd);
	ft_printf("\nLoading map -> ");
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
	map_fill(filename, map);
}

void	map_fill(char *filename, t_map *map)
{
	unsigned int	i;
	int				fd;
	char			*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	ft_printf("\nFilling map points -> ");
	while (line)
	{
		parse_line(line, map, i);
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

void	parse_line(char *line, t_map *map, int line_n)
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
		map->points[start_index + i].x = i;
		map->points[start_index + i].y = line_n;
		map->points[start_index + i].z = ft_atoi(cols[i]);
		if (map->points[start_index + i].z > map->max_z)
			map->max_z = map->points[start_index + i].z;
		if (map->points[start_index + i].z < map->min_z)
			map->min_z = map->points[start_index + i].z;
		map->points[start_index + i].color = get_color(cols[i]);
		i++;
	}
	ft_free_array(cols);
}
