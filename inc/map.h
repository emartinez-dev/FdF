/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:13:14 by franmart          #+#    #+#             */
/*   Updated: 2022/12/11 20:47:53 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MAP_H
# define MAP_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef	struct	s_map {
	int	width;
	int	height;
	int	**map;
} t_map;

void	read_file(char *filename, t_map *map);
int		*read_cols(char *line, t_map *map);

#	endif