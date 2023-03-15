/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:44:53 by franmart          #+#    #+#             */
/*   Updated: 2023/03/15 17:35:02 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	attach_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &exit_help_hook, fdf);
	mlx_loop_hook(fdf->mlx, &movement_hook, fdf);
	mlx_loop_hook(fdf->mlx, &zoom_hook, fdf);
}

void	exit_help_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_J))
	{
		if (fdf->help_on)
		{
			fdf->help->enabled = 0;
			fdf->img->enabled = 1;
			fdf->help_on = 0;
		}
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_H))
	{
		if (!fdf->help_on)
		{
			fdf->help->enabled = 1;
			fdf->img->enabled = 0;
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
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->cam->offset_y += 5;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->cam->offset_x -= 5;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->cam->offset_x += 5;
	else
		return ;
	draw_map(fdf);
}

void	zoom_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_O))
		fdf->cam->zoom *= 1.1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
		fdf->cam->zoom /= 1.1;
	else if (fdf->cam->zoom < 0.01)
		fdf->cam->zoom = 0.01;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_U))
		fdf->cam->z_scale *= 1.1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
		fdf->cam->z_scale /= 1.1;
	else if (fdf->cam->z_scale < 0.01)
		fdf->cam->z_scale = 0.01;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		fdf->cam->projection = ISOMETRIC;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		fdf->cam->projection = TOP;
	else
		return ;
	draw_map(fdf);
}
