/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:51:50 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:51:52 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int			get_default_color(t_orientation orientation)
{
	if (orientation == NORTH)
		return (0xFFFFFF);
	else if (orientation == WEST)
		return (0xAA0000);
	else if (orientation == SOUTH)
		return (0xAAAA00);
	else
		return (0xAA00AA);
}

int			get_ret(t_data *data, int place_x, int place_y, int texture_nbr)
{
	int	ret;

	ret = data->textures[texture_nbr].addr[place_y *
		data->textures[texture_nbr].size_line + place_x * 4];
	ret = ret + (data->textures[texture_nbr].addr[place_y *
		data->textures[texture_nbr].size_line + place_x * 4 + 1] << 8);
	ret = ret + (data->textures[texture_nbr].addr[place_y *
		data->textures[texture_nbr].size_line + place_x * 4 + 2] << 16);
	return (ret);
}

int			get_color(t_data *data, t_hit_info *hit, t_draw_info *di)
{
	int			texture_nbr;
	double		place;
	int			place_x;
	int			place_y;

	texture_nbr = get_texture_nbr(data, hit);
	if (texture_nbr < 0 || texture_nbr > TEXTURE_NBR)
	{
		return (get_default_color(hit->orientation));
	}
	if (hit->side == 0)
		place = hit->collision_pos[1] - (int)hit->collision_pos[1];
	else
		place = hit->collision_pos[0] - (int)hit->collision_pos[0];
	place_x = (int)(place * (double)data->textures_size[texture_nbr][0]);
	place_y = (int)(((double)(di->y - di->real_start) / (double)(di->real_end
		- di->real_start)) * (double)data->textures_size[texture_nbr][1]);
	if (place_x >= data->textures_size[texture_nbr][0])
		place_x--;
	if (place_y >= data->textures_size[texture_nbr][1])
		place_y--;
	return (get_ret(data, place_x, place_y, texture_nbr));
}

void		draw_col(t_data *data, t_hit_info *hit, int x)
{
	int			height;
	int			start;
	int			end;
	t_draw_info	di;

	height = (int)(data->h / hit->corrected_dist);
	start = (int)(data->h / 2. - height / 2.);
	end = (int)(data->h / 2. + height / 2. - 1);
	di.real_start = start;
	if (start < 0)
		start = 0;
	di.real_end = end;
	if (end >= data->h)
		end = data->h - 1;
	di.y = 0;
	while (di.y < data->h)
	{
		if (di.y < start)
			put_pixel_to_image(&data->img, 0x0000AA, x, di.y);
		else if (di.y >= start && di.y <= end)
			put_pixel_to_image(&data->img, get_color(data, hit, &di), x, di.y);
		else
			put_pixel_to_image(&data->img, 0xAAAAAA, x, di.y);
		di.y++;
	}
}
