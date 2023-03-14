/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:13:14 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 19:09:42 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FDF_H
# define FDF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <errno.h>
# include <stdio.h>

/* Constants */
# define WIDTH 1200
# define HEIGHT 1000
# define ISO_ANGLE 0.463646716

/* Error messages */
# define ERR_ARGS "ERROR: you must enter one (1) parameter"
# define ERR_FILEEXT "ERROR: file extension must be .fdf"
# define ERR_FILEOPEN "ERROR: file could not be open"
# define ERR_MAPNOTVALID "ERROR: map could not be parsed"
# define ERR_MAPEMPTY "ERROR: map is empty"
# define ERR_MAPWIDTH "ERROR: map width must be equal on all lines"

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
	double			zoom;
	int				z_scale;
	int				world_x;
	int				world_y;
	double			angle;
	double			origin_x;
	double			origin_y;
	int				min_z;
	int				max_z;
	int				origin_z;
	t_point			*points;
}	t_map;

typedef struct s_fdf
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*g_img;
}	t_fdf;

/* colors.c */
unsigned int	get_color(char *line);
uint32_t		hex_to_rgba(unsigned int hex);

/* draw.c */
void	draw_map(t_map *map, mlx_image_t *g_img, mlx_t *mlx);
void	isometric(t_point *p, t_map *map);

/* map.c */
t_map	*map_init(void);
void	map_load(char *filename, t_map *map);
void	map_fill(char *filename, t_map *map);
int		check_filename(char *filename);

/* map_utils.c */
void	map_free(t_map *map);
int		count_cols(char *line, char sep);
void	parse_line(char *line, t_map *map, int line_n);

/* error.c */
void ft_exit(char *str);

#	endif
