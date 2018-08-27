#include <wolf3d.h>

void	color_to_array(uint pixel, int array[3])
{
	array[0] = (pixel & 0x0000ff) >> 0;
	array[1] = (pixel & 0x00ff00) >> 8;
	array[2] = (pixel & 0xff0000) >> 16;
}

void	apply_filter(t_data *data, unsigned int filter_color, double ratio)
{
	int					x;
	int					y;
	uint			color;
	unsigned int		image_color;
	int					tmp[3];

	x = 0;
	while (x < data->w)
	{
		y = 0;
		while (y < data->h)
		{
			image_color = data->addr[y * data->size_line + x * 4];
			image_color	+= data->addr[y * data->size_line + x * 4 + 1] << 8;
			image_color += data->addr[y * data->size_line + x * 4 + 2] << 16;

			color_to_array(image_color, tmp);
			printf("color : {%d, %d, %d} = %u\n", tmp[0], tmp[1], tmp[2], image_color);
			tmp[0] = (int)(tmp[0] - (255 * .1) < 0. ? 0. : tmp[0] - (255. * .1));
			tmp[1] = (int)(tmp[1] - (255 * .1) < 0. ? 0. : tmp[1] - (255. * .1));
			tmp[2] = (int)(tmp[2] - (255 * .1) < 0. ? 0. : tmp[2] - (255. * .1));
			printf("tmp : {%d, %d, %d}\n", tmp[0], tmp[1], tmp[2]);
			color = (tmp[0] & 0x0000ff) | ((tmp[1] << 8) & 0x00ff00) | ((tmp[2] << 16) & 0xff0000);
		
			put_pixel_to_image(data, color, x, y);
			y++;
		}
		x++;
	}
}

int		get_texture_nbr(t_data *data, t_hit_info *hit)
{
	int	nbr;

	nbr = data->map[hit->collided_wall[0]][hit->collided_wall[1]].num;

	if (nbr == 1)
		return (WOOD_TEXTURE);
	else if (nbr != 4)
		return (nbr - 2);
	else
	{
		if (hit->orientation == NORTH)
			return TWILIGHT_TEXTURE;
		else if (hit->orientation == SOUTH)
			return RDASH_TEXTURE;
		else if (hit->orientation == WEST)
			return WOOD_TEXTURE;
		else
			return STONE_TEXTURE;
	}
}

int		get_color(t_data *data, t_hit_info *hit, int y, int real_start, int real_end)
{
	int	ret;
	int	texture_nbr;
	double	place;
	int			place_x;
	int			place_y;

	texture_nbr = get_texture_nbr(data, hit);
	if (texture_nbr < 0 || texture_nbr > TEXTURE_NBR)
	{
		if (hit->orientation == NORTH)
			ret = 0xFFFFFF;
		else if (hit->orientation == WEST)
			ret = 0xAA0000;
		else if (hit->orientation == SOUTH)
			ret = 0xAAAA00;
		else
			ret = 0xAA00AA;
		return ret;
	}
	if (hit->side == 0)
		place = hit->collision_pos[1] - (int)hit->collision_pos[1];
	else
		place = hit->collision_pos[0] - (int)hit->collision_pos[0];

	place_x = (int)(place * (double)data->textures_size[texture_nbr][0]);
	place_y = (int)(((double)(y - real_start) / (double)(real_end - real_start)) * (double)data->textures_size[texture_nbr][1]);

	ret =  data->textures_addr[texture_nbr][place_y * data->textures_line_size[texture_nbr] + place_x * 4];
	ret = ret + (data->textures_addr[texture_nbr][place_y * data->textures_line_size[texture_nbr] + place_x * 4 + 1] << 8);
	ret = ret + (data->textures_addr[texture_nbr][place_y * data->textures_line_size[texture_nbr] + place_x * 4 + 2] << 16);
	return ret;
}

void	draw_col(t_data *data, t_hit_info *hit, int x)
{
	int	height;
	int	start;
	int	end;
	int	y;
	int real_start;
	int	real_end;

	height = (int)(data->h / hit->corrected_dist);
	start = (int)(data->h / 2. - height / 2.);
	end = (int)(data->h / 2. + height / 2. - 1);
	real_start = start;
	if (start < 0)
		start = 0;
	real_end = end;
	if (end >= data->h)
		end = data->h - 1;

	y = 0;
	while (y < data->h)
	{
		if (y < start) // Partie haute
			put_pixel_to_image(data, 0x0000AA, x, y);
		else if (y >= start && y <= end) // Partie mediane
		{
			put_pixel_to_image(data, get_color(data, hit, y, real_start, real_end), x, y);
		}
		else // Partie basse
			put_pixel_to_image(data, 0xAAAAAA, x, y);
		y++;
	}
}
