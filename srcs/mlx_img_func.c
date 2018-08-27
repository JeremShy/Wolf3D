/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 11:07:47 by jcamhi            #+#    #+#             */
/*   Updated: 2017/05/24 11:07:48 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		get_color_code(int r, int v, int b)
{
	return ((b << 0) + (v << 8) + (r << 16));
}

void	put_pixel_to_image(t_data *data, int color, int x, int y)
{
	size_t		value;

	value = mlx_get_color_value(data->mlx, color);
	(data->addr)[y * data->size_line + x * 4 + 0] = (value & 0x0000ff) >> 0;
	(data->addr)[y * data->size_line + x * 4 + 1] = (value & 0x00ff00) >> 8;
	(data->addr)[y * data->size_line + x * 4 + 2] = (value & 0xff0000) >> 16;
}

void	clear_image(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)(data->h * data->size_line))
	{
		(data->addr)[i] = 0;
		i++;
	}
}

void	fill_image(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->w)
	{
		y = 0;
		while (y < data->h)
		{
			put_pixel_to_image(data, color, x, y);
			y++;
		}
		x++;
	}
}
