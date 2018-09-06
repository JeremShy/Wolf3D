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
