/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:51:58 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:52:00 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int	red_cross_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	free_mlx_and_exit(data);
	return (0);
}
