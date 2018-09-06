/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:52:15 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:52:17 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		handle_error_void(void *variable, void *error_value, char *msg)
{
	if (variable == error_value)
	{
		ft_printf("%s\n", msg);
		return (1);
	}
	return (0);
}

void	free_dtab(t_map_square **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
