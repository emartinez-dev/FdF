/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:13:14 by franmart          #+#    #+#             */
/*   Updated: 2022/12/18 13:58:17 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MAP_H
# define MAP_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000
# define ANGLE 0.52

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_point;

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	len;
	int				zoom;
	int				z_scale;
	t_point			*points;
}	t_map;

/* draw.c */
void	draw_map(t_map *map, mlx_image_t *g_img, mlx_t *mlx);

/* utils.c */
void	free_array(char **arr);

/* map.c */
void	map_init(char *filename, t_map *map);
void	map_fill(char *filename, t_map *map);

/* map_utils.c */
void	map_free(t_map *map);
int		count_cols(char *line, char sep);
void	read_line(char *line, t_map *map, int line_n);
void	map_zoom(t_map *map);

#	endif
