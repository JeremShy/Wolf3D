/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:54:52 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:54:53 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		color_to_array(uint pixel, int array[3])
{
	array[0] = (pixel & 0x0000ff) >> 0;
	array[1] = (pixel & 0x00ff00) >> 8;
	array[2] = (pixel & 0xff0000) >> 16;
}

static void	set_tmp_color(int tmp[3], int *color, double ratio)
{
	tmp[0] = (int)(tmp[0] - (255 * ratio) < 0. ? 0. : tmp[0]
		- (255. * ratio));
	tmp[1] = (int)(tmp[1] - (255 * ratio) < 0. ? 0. : tmp[1]
		- (255. * ratio));
	tmp[2] = (int)(tmp[2] - (255 * ratio) < 0. ? 0. : tmp[2]
		- (255. * ratio));
	*color = (tmp[0] & 0x0000ff) | ((tmp[1] << 8) & 0x00ff00)
		| ((tmp[2] << 16) & 0xff0000);
}

void		darken(t_data *data, double ratio, t_vec3 from, t_vec3 to)
{
	int					x;
	int					y;
	int					color;
	unsigned int		image_color;
	int					tmp[3];

	x = from[0];
	while (x < to[0])
	{
		y = from[1];
		while (y < to[1])
		{
			image_color = data->img.addr[y * data->img.size_line + x * 4]
				& 0xff;
			image_color = image_color | ((data->img.addr[y *
						data->img.size_line + x * 4 + 1] << 8) & 0x00ff00);
			image_color = image_color | ((data->img.addr[y
						* data->img.size_line + x * 4 + 2] << 16) & 0xff0000);
			color_to_array(image_color, tmp);
			set_tmp_color(tmp, &color, ratio);
			put_pixel_to_image(&data->img, color, x, y);
			y++;
		}
		x++;
	}
}

int			get_texture_nbr(t_data *data, t_hit_info *hit)
{
	int	nbr;

	nbr = data->map[hit->collided_wall[0]][hit->collided_wall[1]].num;
	if (nbr == 1)
		return (WOOD_TEXTURE);
	else if (nbr == 5)
		return (PASSAGE_SECRET_TEXTURE);
	else if (nbr != 4)
		return (nbr - 2);
	else
	{
		if (hit->orientation == NORTH)
			return (TWILIGHT_TEXTURE);
		else if (hit->orientation == SOUTH)
			return (RDASH_TEXTURE);
		else if (hit->orientation == WEST)
			return (WOOD_TEXTURE);
		else
			return (STONE_TEXTURE);
	}
}
