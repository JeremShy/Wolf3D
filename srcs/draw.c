#include <wolf3d.h>

int		get_texture_nbr(t_data *data, t_hit_info *hit)
{
	if (data->map[hit->collided_wall[0]][hit->collided_wall[1]] == 1)
		return (-1);
	else if (data->map[hit->collided_wall[0]][hit->collided_wall[1]] == 2)
		return (0);
	else
		return (2);
}

int		get_color(t_data *data, t_hit_info *hit, int x, int y)
{
	int	ret;
	int	texture_nbr;
	void	*texture;
	double	place;
	int			place_x;
	int			place_y;

	texture_nbr = get_texture_nbr(data, hit);
	if (texture_nbr == -1)
	{
		if (hit->side == 0)
			ret = 0xFFFFFF;
		else
			ret = 0xAA0000;
			return ret;
	}
	if (hit->side == 0)
		place = hit->collision_pos[1] - (int)hit->collision_pos[1];
	else
		place = hit->collision_pos[0] - (int)hit->collision_pos[0];

	place_x = (int)(place * (double)data->textures_size[texture_nbr][0]);
	place_y = (int)(((double)y / (double)data->w) * (double)data->textures_size[texture_nbr][1]);

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
	int	full_color;
	int	wall_color;

	height = (int)fabs((data->h / hit->corrected_dist));
	start = (int)(-1. * height / 2. + data->h / 2.);
	end = (int)(height / 2. + data->h / 2.);
	if (data->map[hit->collided_wall[0]][hit->collided_wall[1]] != 1)
		full_color = 0;
	else
	{
		full_color = 1;
		wall_color = get_color(data, hit, x, 0);
	}


	if (start < 0)
		start = 0;
	if (end >= data->h)
		end = data->h - 1;
	y = 0;
	while (y < data->h)
	{
		if (y < start) // Partie haute
			put_pixel_to_image(data, 0x0000AA, x, y);
		else if (y >= start && y <= end) // Partie mediane
		{
			if (full_color)
				put_pixel_to_image(data, wall_color, x, y);
			else
				put_pixel_to_image(data, get_color(data, hit, x, y), x, y);
		}
		else // Partie basse
			put_pixel_to_image(data, 0xAAAAAA, x, y);
		y++;
	}
}
