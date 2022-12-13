/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2022/12/13 16:06:57 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/include/libft.h"
#include "../inc/map.h"
#define DEFAULT_COLOR 255

int		count_cols(char *line)
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

void	read_file(char *filename, t_map *map)
{
	int		fd;
	int		row;
	char	*line;
	char	*trim_line;

	row = 0;
	map_dimensions(filename, map);
	ft_printf("Alto: %d\t Ancho: %d\n", map->height, map->width);
	exit(0);
	map->map = ft_calloc(map->height, sizeof(t_point*)); // aqui también
	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
	{
		trim_line = ft_strtrim(line, " \n");
		map->map[row] = read_cols(trim_line, map, row); // leak aqui
		row++;
		free(line);
		free(trim_line);
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
		point->color = ft_atoi_base(str[1], "0123456789abcdef");
		double_free(str);
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
	//ft_printf("Elementos: %d\n", i);
	i = 0;
	while (text_cells[i])
	{
		cols[i].x = i;
		cols[i].z = row;
		read_cell(line, &cols[i]);
		//ft_printf("Free n%d\n", i);
		//ft_printf("celda x:%d\ty:%d\tz:%d\tcolor:%u\n", cols[i].x, cols[i].y, cols[i].z, cols[i].color);
		i++;
	}
	//ft_printf("Free n%d\n", i);
	double_free(text_cells);
	return (cols);
}

int	main(int argc, char **argv)
{
	t_map	map;

	read_file(argv[1], &map);
	return (0);
}
