/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2022/12/12 23:21:35 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/include/libft.h"
#include "../inc/map.h"
#define DEFAULT_COLOR 255

void	count_lines(char *filename, t_map *map)
{
	unsigned int	i;
	int				fd;
	char			*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
	{
		free(line);
		i++;
		line = ft_gnl(fd);
	}
	free(line);
	map->height = i;
	close(fd);
}

void	read_file(char *filename, t_map *map)
{
	int		fd;
	int		row;
	char	*line;
	char	*trim_line;

	row = 0;
	count_lines(filename, map);
	map->map = ft_calloc(map->height, sizeof(t_point)); // aqui también
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
	{
		trim_line = ft_strtrim(line, " \n");
		free(line);
		map->map[row] = read_cols(trim_line, map, row); // leak aqui
		free(trim_line);
		row++;
		line = ft_gnl(fd);
	}
	free(line);
	close(fd);
}

// esta no leakea
void	read_cell(char *line, t_point *point)
{
	char	**str;

	if (ft_strchr(line, ',') != 0)
	{
		str = ft_split(line, ',');
		point->y = ft_atoi(str[0]);
		free(str[0]);
		point->color = ft_atoi_base(str[1], "0123456789abcdef");
		free(str[1]);
		free(str);
	}
	else
	{
		str = 0;
		point->y = ft_atoi(line);
		point->color = DEFAULT_COLOR;
	}
}

t_point	*read_cols(char *line, t_map *map, int row)
{
	char	**text_cells;
	t_point	*cols;
	int		i;

	i = 0;
	text_cells = ft_split(line, ' ');
	while (text_cells[i])
		i++;
	if (row == 0)
		map->width = i;
	if (map->width != i)
		exit(1);
	//ft_printf("line: %s width: %d\n", line, map->width);
	cols = ft_calloc(i, sizeof(t_point)); // leak aqui de 10 elementos
	ft_printf("Elementos: %d\n", i);
	i = 0;
	while (text_cells[i])
	{
		cols[i].x = i;
		cols[i].z = row;
		read_cell(line, &cols[i]);
		ft_printf("Free n%d\n", i);
		free(text_cells[i]);
		//ft_printf("celda x:%d\ty:%d\tz:%d\tcolor:%u\n", cols[i].x, cols[i].y, cols[i].z, cols[i].color);
		i++;
	}
	ft_printf("Free n%d\n", i);
	free(text_cells[i]);
	free(text_cells);
	return (cols);
}

int	main(int argc, char **argv)
{
	t_map	map;

	map.width = 0;
	read_file(argv[1], &map);
	return (0);
}
