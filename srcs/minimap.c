/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:51:57 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:51:58 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_map_square(t_data *d, int minimap_size[2], int row, int col)
{
	t_vec3	square_size;
	int		x_p;
	int		y_p;
	int		num;

	num = d->map[row][col].num;
	ft_vec3_init(square_size, (double[]){
		minimap_size[1] / (double)d->size_x,
		minimap_size[0] / (double)d->size_y, 0});
	x_p = row * square_size[1];
	while (x_p < (row + 1) * square_size[1])
	{
		y_p = col * square_size[0];
		while (y_p < (col + 1) * square_size[0])
		{
			put_pixel_to_image_transparency(&d->minimap,
				num != 0 ? 0x88FFFFFF : 0x88000000, x_p, y_p);
			y_p++;
		}
		x_p++;
	}
}

void	draw_player_cross(t_data *data,
	t_vec3 minimap_start, t_vec3 minimap_end)
{
	t_vec3	player_pos;

	ft_vec3_init(player_pos, (double[]){
		data->cam_pos[0] * data->w / data->size_y,
		data->cam_pos[1] * data->h / data->size_x,
	});
	put_pixel_to_image_transparency(&data->minimap, 0x00FF0000,
		player_pos[0] * (minimap_end[0] - minimap_start[0]) / data->w,
		player_pos[1] * (minimap_end[1] - minimap_start[1]) / data->h);
	put_pixel_to_image_transparency(&data->minimap, 0x00FF0000,
		player_pos[0] * (minimap_end[0] - minimap_start[0]) / data->w - 1,
		player_pos[1] * (minimap_end[1] - minimap_start[1]) / data->h);
	put_pixel_to_image_transparency(&data->minimap, 0x00FF0000,
		player_pos[0] * (minimap_end[0] - minimap_start[0]) / data->w + 1,
		player_pos[1] * (minimap_end[1] - minimap_start[1]) / data->h);
	put_pixel_to_image_transparency(&data->minimap, 0x00FF0000,
		player_pos[0] * (minimap_end[0] - minimap_start[0]) / data->w,
		player_pos[1] * (minimap_end[1] - minimap_start[1]) / data->h - 1);
	put_pixel_to_image_transparency(&data->minimap, 0x00FF0000,
		player_pos[0] * (minimap_end[0] - minimap_start[0]) / data->w,
		player_pos[1] * (minimap_end[1] - minimap_start[1]) / data->h + 1);
}

void	load_minimap(t_data *d, t_vec3 m_start, t_vec3 m_end)
{
	int	row;
	int	col;

	ft_vec3_init(m_start, (double[]){0, 0, 0});
	ft_vec3_init(m_end, (double[]){d->w / 4, d->h / 4, 0});
	d->minimap.img = mlx_new_image(d->mlx, m_end[0] - m_start[0],
		m_end[1] - m_start[1]);
	d->minimap.addr = mlx_get_data_addr(d->minimap.img,
		&d->img.bpp, &d->minimap.size_line, &d->minimap.endian);
	row = 0;
	while (row < d->size_y)
	{
		col = 0;
		while (col < d->size_x)
		{
			draw_map_square(d, (int[2]){m_end[0] -
				m_start[0], m_end[1] - m_start[1]}, row, col);
			col++;
		}
		row++;
	}
	d->minimap_save = malloc(d->minimap.size_line * (d->w / 4) * sizeof(char));
	ft_memcpy(d->minimap_save, d->minimap.addr,
		d->minimap.size_line * (d->w / 4.));
}

void	draw_minimap(t_data *d)
{
	static int		loaded = 0;
	static t_vec3	minimap_start;
	static t_vec3	minimap_end;

	if (loaded == 0)
	{
		load_minimap(d, minimap_start, minimap_end);
		loaded = 1;
	}
	ft_memcpy(d->minimap.addr, d->minimap_save,
		d->minimap.size_line * (d->w / 4.));
	draw_player_cross(d, minimap_start, minimap_end);
	mlx_put_image_to_window(d->mlx, d->win, d->minimap.img,
		minimap_start[0], minimap_start[1]);
}
