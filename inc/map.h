/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:13:14 by franmart          #+#    #+#             */
/*   Updated: 2022/12/13 15:25:50 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MAP_H
# define MAP_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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
	t_point			**map;
} t_map;

void	read_file(char *filename, t_map *map);
t_point	*read_cols(char *line, t_map *map, int row);
void	double_free(char **arr);

#	endif