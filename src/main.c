/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:44:23 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 10:59:55 by franmart         ###   ########.fr       */
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

void	hook2(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->cam->offset_y -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->cam->offset_y += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->cam->offset_x -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->cam->offset_x += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
		fdf->cam->zoom *= 1.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
		fdf->cam->zoom /= 1.1;
	if (fdf->cam->zoom < 0.01)
		fdf->cam->zoom = 0.01;
	draw_map(fdf);
}

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
	fdf.g_img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.g_img)
		exit(EXIT_FAILURE);
	init_cam(&fdf);
	draw_map(&fdf);
	mlx_loop_hook(fdf.mlx, &hook, &fdf);
	mlx_loop_hook(fdf.mlx, &hook2, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free(fdf.cam);
	map_free(fdf.map);
	return (0);
}
