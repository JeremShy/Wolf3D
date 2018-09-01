#include <wolf3d.h>

void	draw_map_square(t_data *data, t_vec3 minimap_start, t_vec3 minimap_end, int row, int col)
{
	t_vec3	square_size;
	int		x_pixel;
	int		y_pixel;
	int		num;

	num = data->map[row][col].num;
	ft_vec3_init(square_size, (double[]){
		(minimap_end[1] - minimap_start[1]) / (double)data->size_x,
		(minimap_end[0] - minimap_start[0]) / (double)data->size_y,
		0
	});
	x_pixel = row * square_size[1];
	while (x_pixel < (row + 1) * square_size[1])
	{
		y_pixel = col * square_size[0];
		while (y_pixel < (col + 1) * square_size[0])
		{
			if (num != 0)
				put_pixel_to_image_transparency(&data->minimap, 0x88FFFFFF, x_pixel, y_pixel);
			else
				put_pixel_to_image_transparency(&data->minimap, 0x88000000, x_pixel, y_pixel);
			y_pixel++;
		}
		x_pixel++;
	}
}

void	draw_player_cross(t_data *data, t_vec3 minimap_start, t_vec3 minimap_end)
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

void	draw_minimap(t_data *data)
{
	static int loaded = 0;
	static t_vec3	minimap_start;
	static t_vec3	minimap_end;
	int		row;
	int		col;

	if (loaded == 0)
	{
		loaded = 1;
		ft_vec3_init(minimap_start, (double[]){0, 0, 0});
		ft_vec3_init(minimap_end, (double[]){data->w / 4, data->h / 4, 0});

		data->minimap.img = mlx_new_image(data->mlx, minimap_end[0] - minimap_start[0], minimap_end[1] - minimap_start[1]);
		data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->img.bpp, &data->minimap.size_line, &data->minimap.endian);
		row = 0;
		while (row < data->size_y)
		{
			col = 0;
			while(col < data->size_x)
			{
				draw_map_square(data, minimap_start, minimap_end, row, col);
				col++;
			}
			row++;
		}
		data->minimap_save = malloc(data->minimap.size_line * (data->w  / 4) * sizeof(char));
		ft_memcpy(data->minimap_save, data->minimap.addr, data->minimap.size_line * (data->w / 4.));
	}
	ft_memcpy(data->minimap.addr, data->minimap_save, data->minimap.size_line * (data->w / 4.));
	draw_player_cross(data, minimap_start, minimap_end);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, minimap_start[0], minimap_start[1]);
}