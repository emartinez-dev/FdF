/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:44:23 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 17:08:08 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int32_t	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc != 2)
		return (1);
	fdf.map = map_init();
	map_load(argv[1], fdf.map);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "franmart-FdF", true);
	if (!fdf.mlx)
		exit(EXIT_FAILURE);
	fdf.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.img)
		exit(EXIT_FAILURE);
	init_cam(&fdf);
	draw_instructions(&fdf);
	draw_map(&fdf);
	attach_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free(fdf.cam);
	map_free(fdf.map);
	return (0);
}
