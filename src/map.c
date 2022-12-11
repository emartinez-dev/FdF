/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:23:19 by franmart          #+#    #+#             */
/*   Updated: 2022/12/11 21:23:09 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/include/libft.h"
#include "../inc/map.h"

void	read_file(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		*col;

	fd = open(filename, O_RDONLY);
	line = ft_gnl(fd);
	while (line)
	{
		map->height += 1;
		col = read_cols(line, map);
		// meter las col en un arr de cols dentro del objeto map
		free(col);
		line = ft_gnl(fd);
	}
	free(line);
	close(fd);
	ft_printf("Tamaño mapa: %dx%d\n", map->height, map->width);
}

int	*read_cols(char *line, t_map *map)
{
	char	**arr;
	char	*clean_line;
	int		*cols;
	int		i;

	i = 0;
	clean_line = ft_strtrim(line, "\n ");
	free(line);
	arr = ft_split(clean_line, ' ');
	while (arr[i])
		i++;
	map->width = i;
	cols = ft_calloc(i, sizeof(int));
	i = 0;
	while (arr[i])
	{
		/* TODO: hay que reescribir esta mierda otra vez porque nadie me avisó
			de que pueden añadir los colores al mapa XD */
		if (ft_strchr(arr[i], ','))
			exit(1);
		cols[i] = ft_atoi(arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	free(clean_line);
	return (cols);
}

int	main(int argc, char **argv)
{
	t_map	map;

	map.height = 0;
	map.width = 0;
	read_file(argv[1], &map);
	return (0);
}
