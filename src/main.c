/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:44:23 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 15:46:29 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"



int32_t	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc != 2)
		return (1);
	fdf.help_on = 0;
	fdf.map = map_init();
	map_load(argv[1], fdf.map);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "franmart-FdF", true);
	if (!fdf.mlx)
		exit(EXIT_FAILURE);
	fdf.g_img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	fdf.help = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.g_img || !fdf.help)
		exit(EXIT_FAILURE);
	init_cam(&fdf);
	draw_map(&fdf);
	mlx_loop_hook(fdf.mlx, &exit_help_hook, &fdf);
	mlx_loop_hook(fdf.mlx, &movement_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free(fdf.cam);
	map_free(fdf.map);
	return (0);
}
