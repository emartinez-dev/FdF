/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2022/12/13 20:16:43 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

#define DEFAULT_COLOR 255
#define BASE_HEX	"0123456789abcdef"

void	map_init(char *filename, t_map *map)
{
	int		fd;
	int		row;
	char	*line;
	char	*trim_line;

	row = 0;
	map_alloc(filename, map);
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line != NULL)
	{
		trim_line = ft_strtrim(line, " \n");
		read_row(trim_line, map, row);
		row++;
		free(line);
		free(trim_line);
		line = ft_gnl(fd);
	}
	close(fd);
}

void	read_row(char *line, t_map *map, int row)
{
	char	**text_cells;
	char	**str;
	int		i;

	i = -1;
	text_cells = ft_split(line, ' ');
	while (text_cells[++i])
	{
		map->points[row][i].x = i;
		map->points[row][i].z = row;
		if (ft_strchr(line, ',') != 0)
		{
			str = ft_split(line, ',');
			map->points[row][i].y = ft_atoi(str[0]);
			map->points[row][i].color = ft_atoi_base(str[1], BASE_HEX);
			free_array(str);
		}
		else
		{
			str = 0;
			map->points[row][i].y = ft_atoi(text_cells[i]);
			map->points[row][i].color = DEFAULT_COLOR;
		}
	}
	free_array(text_cells);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		r;
	int		c;

	r = 0;
	map_init(argv[1], &map);
	/*
	while (r < map.height)
	{
		c = 0;
		while (c < map.width)
		{
			ft_printf("Celda (%d,%d)\nValores: x%d y%d z%d color %x\n\n", r, c,
				map.points[r][c].x,
				map.points[r][c].y,
				map.points[r][c].z,
				map.points[r][c].color
				);
			c++;
		}
		r++;
	}
	*/
	map_free(&map);
	return (0);
}
