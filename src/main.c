/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:44:23 by franmart          #+#    #+#             */
/*   Updated: 2023/03/14 18:50:03 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

void	print_points(t_map *map)
{
	unsigned int	i;

	i = -1;
	while (++i < map->width * map->height)
		printf("x: %d\t y: %d\t z: %d\n", map->points[i].x, map->points[i].y, map->points[i].z);
}

int32_t	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc != 2)
		return (1);
	fdf.map = map_init();
	map_load(argv[1], fdf.map);
	print_points(fdf.map);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "franmart-FdF", true);
	if (!fdf.mlx)
		exit(EXIT_FAILURE);
	fdf.g_img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.g_img)
		exit(EXIT_FAILURE);
	//draw_map(&map, g_img, mlx);
	mlx_loop_hook(fdf.mlx, &hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (0);
}
