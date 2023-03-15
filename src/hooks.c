/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:44:53 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 15:46:29 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	exit_help_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_H))
	{
		if (fdf->help_on)
		{
			fdf->help->enabled = 0;
			fdf->help_on = 0;
		}

	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_J))
	{
		if (!fdf->help_on)
		{
			fdf->help->enabled = 1;
			fdf->help_on = 1;
		}
	}
}

void	movement_hook(void *param)
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
