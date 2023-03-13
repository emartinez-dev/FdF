/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:29:33 by franmart          #+#    #+#             */
/*   Updated: 2023/03/13 10:04:36 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void ft_exit(char *str)
{
	if (errno == 0)
	{
		ft_putstr_fd("\n", 2);
		ft_putendl_fd(str, 2);
	}
	else
		perror(str);
	exit(1);
}
