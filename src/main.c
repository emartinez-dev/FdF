/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2022/12/17 20:38:12 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/include/libft.h"
#include "../inc/fdf.h"
#include <math.h>
#define WIDTH 1000
#define HEIGHT 1500
#define ZOOM 20
#define ANGLE 0.52

mlx_image_t	*g_img;

void	isometric(t_point *point)
{
	float	x1;
	float	y1;

	x1 = (point->x - point->y) * cos(ANGLE);
	y1 = (point->x + point->y) * sin(ANGLE) - point->z;
	//ft_printf("x_og: %d\ty_og: %d\n", point->x, point->y);
	point->x = x1;
	point->y = y1;
	//ft_printf("x_new: %d\ty_new:%d\n\n", point->x, point->y);
}

void	bresenham(t_point p0, t_point p1, mlx_image_t *img)
{
	int	dx;
	int	dy;
	int	error;
	int	sx;
	int	sy;

	isometric(&p0);
	isometric(&p1);
	sx = p0.x < p1.x ? 1 : -1;
	sy = p0.y < p1.y ? 1 : -1;
	dx = abs(p1.x - p0.x);
	dy = -abs(p1.y - p0.y);
	error = dx + dy;
	while (1)
	{
		mlx_put_pixel(img, p0.x +400, p0.y + 300, 255);
		if (p0.x == p1.x && p0.y == p1.y) break;
		if (2 * error >= dy)
		{
			if (p0.x == p1.x) break;
			error += dy;
			p0.x += sx;
		}
		if (2 * error <= dx)
		{
			if (p0.y == p1.y) break;
			error += dx;
			p0.y += sy;
		}
	}
}

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 2;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 2;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 2;
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_map	map;
	int		i;
	int		j;

	map_init(argv[1], &map);
	map_fill(argv[1], &map);
	ft_printf("Alto: %d\nAncho: %d\nLongitud: %d\n\n", map.height, map.width, map.len);
	//ft_printf("X:%d\tY:%d\tZ:%d\t\n", map.points[i].x,
		//map.points[i].y, map.points[i].z);

	//inicio MLX loop
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 1200, 1200);
	i = 0;
	while (i < map.len)
	{
		if (map.points[i].x < (map.width - 1) * ZOOM)
			bresenham(map.points[i], map.points[i + 1], g_img);
		if (map.points[i].y < (map.height - 1) * ZOOM)
			bresenham(map.points[i], map.points[i + map.width], g_img);
		i++;
	}
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
