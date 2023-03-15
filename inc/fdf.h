/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:13:14 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 17:34:48 by franmart         ###   ########.fr		  */
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

/* Constants
ISO_ANGLE is 26.5 degrees to radians. We use this instead of 30 degrees because
in computer graphics this is more visually apealing */
# define WIDTH 1200
# define HEIGHT 1000
# define ISO_ANGLE 0.463646716
# define ROTATION_SPEED 0.05
# define MOVE_SPEED 5

/* Error messages */
# define ERR_ARGS "ERROR: you must enter one (1) parameter"
# define ERR_FILEEXT "ERROR: file extension must be .fdf"
# define ERR_FILEOPEN "ERROR: file could not be open"
# define ERR_MAPNOTVALID "ERROR: map could not be parsed"
# define ERR_MAPEMPTY "ERROR: map is empty"
# define ERR_MAPWIDTH "ERROR: map width must be equal on all lines"

/* Instructions */
# define I_INTRO "FDF INSTRUCTIONS"
# define I_QUIT "ESC: quit FdF"
# define I_CLOSE_HELP "J: close help"
# define I_MOVE "WASD: camera movement"
# define I_ZOOM "O/P: Zoom in/out"
# define I_ISO "1/2: Isometric / Top view"
# define I_ZSCALE "U/I: Increase / Decrease z scale"
# define I_ROT_X "2/8: rotate around x axis"
# define I_ROT_Y "4/6: rotate around y axis"
# define I_ROT_Z "7/9: rotate around z axis"
# define I_ROT_RESET "5: reset camera"

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	uint32_t		color;
}	t_point;

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	len;
	int				min_z;
	int				max_z;
	t_point			*points;
}	t_map;

typedef struct s_cam
{
	int		projection;
	float	zoom;
	double	z_scale;
	int		offset_x;
	int		offset_y;
	double	x_angle;
	double	y_angle;
	double	z_angle;
}	t_cam;

typedef struct s_fdf
{
	t_map		*map;
	t_cam		*cam;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*help;
	int			help_on;
}	t_fdf;

typedef struct s_bresenham
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			error;
	int			steps;
	int			init_x;
	int			init_y;
}	t_bresenham;

enum e_projections
{
	TOP,
	ISOMETRIC
};

/* colors.c */
unsigned int	get_color(char *line);
uint32_t		hex_to_rgba(unsigned int hex);
uint32_t		interpolate_color(t_point p0, t_point p1, t_bresenham bres);

/* camera.c */
void			init_cam(t_fdf *fdf);
void			reset_cam(t_fdf *fdf);

/* draw.c */
void			bresenham(t_point p0, t_point p1, mlx_image_t *img);
void			draw_map(t_fdf *fdf);
void			draw_instructions(t_fdf *fdf);

/* draw_utils.c */
void			clear_background(t_fdf *fdf);
int				pixel_limits(t_point *point);
void			init_bresenham(t_point p0, t_point p1, t_bresenham *bres);

/* map.c */
t_map			*map_init(void);
void			map_load(char *filename, t_map *map);
void			map_fill(char *filename, t_map *map);
int				check_filename(char *filename);

/* map_utils.c */
void			map_free(t_map *map);
int				count_cols(char *line, char sep);
void			parse_line(char *line, t_map *map, int line_n);

/* geometry.c */
t_point			project_pt(t_point p, t_fdf *fdf);
void			rotate_x(t_point *pt, t_fdf *fdf);
void			rotate_y(t_point *pt, t_fdf *fdf);
void			rotate_z(t_point *pt, t_fdf *fdf);

/* hooks.c */
void			attach_hooks(t_fdf *fdf);
void			exit_help_hook(void *param);
void			movement_hook(void *param);
void			zoom_hook(void *param);
void			rotate_hook(void *param);

/* error.c */
void			ft_exit(char *str);

/* bonus.c */
void			rainbow_mode(t_map *map);
void			bonus_hook(void *param);
uint32_t		random_color(char r1, char g1, char b1);

#	endif
