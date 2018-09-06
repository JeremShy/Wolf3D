/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 11:07:47 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:52:04 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		get_color_code(int r, int v, int b)
{
	return ((b << 0) + (v << 8) + (r << 16));
}

void	put_pixel_to_image(t_img *img, int color, int x, int y)
{
	(img->addr)[y * img->size_line + x * 4 + 0] = (color & 0x0000ff) >> 0;
	(img->addr)[y * img->size_line + x * 4 + 1] = (color & 0x00ff00) >> 8;
	(img->addr)[y * img->size_line + x * 4 + 2] = (color & 0xff0000) >> 16;
}

void	put_pixel_to_image_transparency(t_img *img, int64_t color, int x, int y)
{
	(img->addr)[y * img->size_line + x * 4 + 0] = (color & 0x000000ff) >> 0;
	(img->addr)[y * img->size_line + x * 4 + 1] = (color & 0x0000ff00) >> 8;
	(img->addr)[y * img->size_line + x * 4 + 2] = (color & 0x00ff0000) >> 16;
	(img->addr)[y * img->size_line + x * 4 + 3] = (color & 0xff000000) >> 24;
}

void	clear_image(t_img *img, size_t h)
{
	size_t	i;

	i = 0;
	while (i < (size_t)(h * img->size_line))
	{
		(img->addr)[i] = 0;
		i++;
	}
}

void	fill_image(t_img *img, size_t w, size_t h, int color)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			put_pixel_to_image(img, color, x, y);
			y++;
		}
		x++;
	}
}
