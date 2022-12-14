/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2022/12/14 23:53:47 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

unsigned int	get_height(char *filename)
{
	char			*line;
	int				fd;
	unsigned int	height;

	height = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
	{
		height++;
		free(line);
		line = ft_gnl(fd);
	}
	free(line);
	return (height);
}

unsigned int	get_width(char *filename)
{
	char			*line;
	int				fd;
	char			**words;
	unsigned int	i;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	words = ft_split(line, ' ');
	while (words[i] && words[i][0] != '\n')
		i++;
	free(line);
	free_array(words);
	return (i);
}

void	map_alloc(char *filename, t_map *map)
{
	int		i;

	i = 0;
	map->height = get_height(filename);
	map->width = get_width(filename);
	map->points = ft_calloc(map->height, sizeof(t_point *));
	while (i < map->height)
	{
		map->points[i] = ft_calloc(map->width, sizeof(t_point));
		i++;
	}
}

void	map_fill(char *filename, t_map *map)
{
	unsigned int	i;
	unsigned int	j;
	int				fd;
	char			*line;
	char			**cols;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
	{
		j = 0;
		cols = ft_split(line, ' ');
		while (cols[j] && cols[j][0] != '\n')
		{
			map->points[i][j].z = ft_atoi(cols[j]);
			j++;
		}
		free_array(cols);
		free(line);
		line = ft_gnl(fd);
		i++;
	}
	free(line);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_map	map;

	// hay que validar la entrada
	map.height = get_height(argv[1]);
	map.width = get_width(argv[1]);
	map_alloc(argv[1], &map);
	map_fill(argv[1], &map);
	ft_printf("Alto: %d\nAncho: %d\n", map.height, map.width);
	return (0);
}