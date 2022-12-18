/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:12:46 by franmart          #+#    #+#             */
/*   Updated: 2022/12/18 10:57:56 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/include/libft.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
