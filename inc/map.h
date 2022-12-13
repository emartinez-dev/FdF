/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:13:14 by franmart          #+#    #+#             */
/*   Updated: 2022/12/13 20:10:29 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MAP_H
# define MAP_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
} t_point;

typedef	struct	s_map
{
	unsigned int	width;
	unsigned int	height;
	t_point			**points;
} t_map;

void	free_array(char **arr);
int		count_cols(char *line);
void	read_row(char *line, t_map *map, int row);
void	map_init(char *filename, t_map *map);
void	map_alloc(char *filename, t_map *map);
void	map_free(t_map *map);
void	map_measure(char *filename, t_map *map);

#	endif