/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:52:05 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:40:13 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	pause_or_unpause(t_data *data)
{
	data->paused = (data->paused ? 0 : 1);
	data->going_front = 0;
	data->going_right = 0;
	data->going_left = 0;
	data->going_back = 0;
	data->rotating_right = 0;
	data->rotating_left = 0;
	data->must_refresh = 1;
}

static void	handle_key(t_data *data, int keycode)
{
	if (keycode == 13)
		data->going_front = 1;
	else if (keycode == 1)
		data->going_back = 1;
	else if (keycode == 123)
	{
		data->rotating_left = 1;
		data->rotating_right = 0;
	}
	else if (keycode == 124)
	{
		data->rotating_left = 0;
		data->rotating_right = 1;
	}
	else if (keycode == 0)
		data->going_left = 1;
	else if (keycode == 2)
		data->going_right = 1;
	else if (keycode == 35)
		pause_or_unpause(data);
}

int			key_press_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (keycode == 53)
	{
		free_dtab(data->map, data->size_y);
		free_mlx_and_exit(data);
	}
	if (!data->paused || keycode == 35)
		handle_key(data, keycode);
	return (1);
}

int			key_release_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (keycode == 13)
		data->going_front = 0;
	else if (keycode == 1)
		data->going_back = 0;
	else if (keycode == 123)
		data->rotating_left = 0;
	else if (keycode == 124)
		data->rotating_right = 0;
	else if (keycode == 0)
		data->going_left = 0;
	else if (keycode == 2)
		data->going_right = 0;
	return (1);
}
